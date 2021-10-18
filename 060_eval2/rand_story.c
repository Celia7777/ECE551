#include "rand_story.h"

#include <ctype.h>
#include <string.h>

//To parse the input template story//
//given the file stream f, return a line_t//
//which contains the array of lines of this story//
//and how many lines//
line_t * parseStory(FILE * f) {
  line_t * parseinp;
  parseinp = malloc(sizeof(*parseinp));
  char * line = NULL;
  size_t sz;
  parseinp->lineinp = NULL;
  parseinp->num_line = 0;
  while (getline(&line, &sz, f) >= 0) {
    parseinp->lineinp =
        realloc(parseinp->lineinp, (parseinp->num_line + 1) * sizeof(*parseinp->lineinp));
    parseinp->lineinp[parseinp->num_line] = line;
    line = NULL;
    parseinp->num_line++;
  }
  free(line);
  return parseinp;
}

//to check if the category in "_category_" in the
//catarray_t(the output after parsing the word.txt) or not
size_t checkIsincatarray(char * category, catarray_t * sample) {
  //if category is in catarray_t, if it is, return 1
  //if not, return 0
  for (size_t i = 0; i < sample->n; i++) {
    if (strcmp(category, sample->arr[i].name) == 0) {
      return 1;
    }
  }
  return 0;
}

//given an extracted category from _category_
//check if it is a valid integer, if it is
//return the exac numeric value eg "_2_" is integer 2
//if it is not, return 0
size_t checkIsvalidinteger(char * category, size_t size) {
  size_t checkans;
  for (size_t i = 0; i < size; i++) {
    if (isdigit(category[i] == 0)) {
      checkans = 0;
      return checkans;
    }
    checkans = atoi(category);
  }
  return checkans;
}

//given two pointers points to the start and next "_"//
//at the string "_xxx_", return xxx//
char * extractCategory(char * front_unds, char * back_unds) {
  size_t len = back_unds - front_unds - 1;  //the length of xxx
  //what if len==0????? "__"
  char * cat_cp;
  //copy xxx into a new string
  //don't forget to free the cat_cp
  cat_cp = strndup(front_unds + 1, len);
  //printf("extractword:%s\n", cat_cp);
  return cat_cp;
}

//given the string "xxx" in "_xxx_"//
//return the replaceword at xxx//
const char * replaceWord(char * category, catarray_t * catg_word, category_t * usedw) {
  const char * replaceword;
  size_t cat_len = strlen(category);
  //if catarray is NULL, replaceword is cat
  if (catg_word == NULL) {
    replaceword = chooseWord(category, catg_word);
    return replaceword;
  }

  //check the type of cat_cp: integer? category? neither?//
  //use some variables to check//
  size_t checkinteger;
  size_t checkcatg;
  checkcatg = checkIsincatarray(category, catg_word);
  checkinteger = checkIsvalidinteger(category, cat_len);
  //printf("check integer:%zu\n", checkinteger);
  //if it is a valid integer of at least one
  //replace it with  the previous used word
  //counting backwards from the current word
  //what if n_words<integer, not enough used words,failure??????
  if (checkinteger >= 1 && usedw->n_words >= checkinteger) {
    replaceword = usedw->words[usedw->n_words - checkinteger];
    //    printf("if it is a valid interger, replace :%s\n", replaceword);
    return replaceword;
  }
  //if cat_cp is in catarray_t, return a random choice
  else if (checkcatg == 1) {
    replaceword = chooseWord(category, catg_word);
    //printf("if it is a valid category, replace :%s\n", replaceword);
    return replaceword;
  }
  //if it is neither in catarray nor a valid integer
  else if (checkcatg == 0 && checkinteger == 0) {
    fprintf(stderr, "the category is neither in catarray nor a valid integer.\n ");
    exit(EXIT_FAILURE);
  }
  else {
    return NULL;
  }
}

//if I have one _ in a line//
//check if we have another at the back//
//if have, return a pointer to next _//
//if not, exit with error info//
char * checkNextUnderscore(char * current_unds) {
  char * next_unds = strchr(current_unds + 1, '_');
  if (next_unds == NULL) {
    fprintf(stderr, "the _ does not followed by another _\n");
    exit(EXIT_FAILURE);
  }
  else {
    return next_unds;
  }
}

//given a line_t story//
//check if it contains _ or not//
//if not, exit with error info//
void checkIfhasUnderscore(line_t * story) {
  size_t count_null = 0;
  char * unds_checkall;
  for (size_t i = 0; i < story->num_line; i++) {
    unds_checkall = strchr(story->lineinp[i], '_');
    if (unds_checkall == NULL) {
      count_null++;
    }
  }
  if (count_null == story->num_line) {
    fprintf(stderr, "input story has no _\n");
    exit(EXIT_FAILURE);
  }
}

catarray_t * processReuseOption(catarray_t * oldcat, char * name, const char * usedword) {
  //keep in mind that c is the new catarray_t this function
  //needs to return, use c just to shorten the sentences
  catarray_t * c;
  //no influence on name and n, just copy(deep copy)
  //initialize words in ready to realloc later
  c = malloc(sizeof(*c));
  c->n = oldcat->n;
  c->arr = malloc(c->n * sizeof(*c->arr));
  for (size_t i = 0; i < oldcat->n; i++) {
    c->arr[i].name = strdup(oldcat->arr[i].name);
    c->arr[i].words = NULL;
    c->arr[i].n_words = 0;
  }
  //to copy the words which are not used before
  for (size_t i = 0; i < oldcat->n; i++) {
    if (strcmp(name, oldcat->arr[i].name) == 0) {
      for (size_t j = 0; j < oldcat->arr[i].n_words; j++) {
        if (strcmp(usedword, oldcat->arr[i].words[j]) != 0) {
          c->arr[i].words = realloc(c->arr[i].words,
                                    (c->arr[i].n_words + 1) * sizeof(*c->arr[i].words));
          c->arr[i].words[c->arr[i].n_words] = strdup(oldcat->arr[i].words[j]);
          c->arr[i].n_words++;
        }
      }
    }
    else {
      c->arr[i].n_words = oldcat->arr[i].n_words;
      c->arr[i].words = malloc(oldcat->arr[i].n_words * sizeof(*c->arr[i].words));
      for (size_t k = 0; k < oldcat->arr[i].n_words; k++) {
        c->arr[i].words[k] = strdup(oldcat->arr[i].words[k]);
      }
    }
  }
  return c;
}

//To create the output story based on the input template//
//given a input line_t, modify its array of lines//
//modify _xxx_ with the corresponding replace words//
//from the word-category catarray_t
//eg. _animal_ into dog//
//add the option to prevent reuse word//
//if option is 0,allow reuse; if it is 1, prevent//
void createOutputStory(line_t * story, catarray_t * catwd_pairs, int option) {
  //check if the input has no "_"//
  //  checkIfhasUnderscore(story);

  //keep track of used words
  //record the previous used words in category_t
  category_t * prevUsedwd;
  prevUsedwd = malloc(sizeof(*prevUsedwd));  //remember to free at last
  prevUsedwd->n_words = 0;
  prevUsedwd->words = NULL;
  prevUsedwd->name = NULL;  //no need to use name

  //modify the input line_t//
  //to copy the string of lines into linecopy
  //and record its size
  char * linecopy = NULL;
  size_t numcopy = 0;
  //to mark the movement of the ptr at the lines
  //and mark the next _
  char * ptr_recrd;
  char * next_unds;
  //the extracted category in input template
  char * catintemp;
  //to get the replace word corresponding to a category
  //and get its length
  const char * rep_word;
  size_t repw_len;

  catarray_t * free_ptr = catwd_pairs;

  for (size_t i = 0; i < story->num_line; i++) {
    if (linecopy == NULL) {
      linecopy = malloc(sizeof(*linecopy));
      linecopy[0] = '\0';
    }
    ptr_recrd = story->lineinp[i];
    while (*ptr_recrd != '\0') {
      if (*ptr_recrd != '_') {
        linecopy = realloc(linecopy, (numcopy + 2) * sizeof(*linecopy));
        linecopy[numcopy] = *ptr_recrd;
        linecopy[numcopy + 1] = '\0';
        ptr_recrd++;
        numcopy++;
      }
      else {
        next_unds = checkNextUnderscore(ptr_recrd);
        catintemp = extractCategory(ptr_recrd, next_unds);
        rep_word = replaceWord(catintemp, catwd_pairs, prevUsedwd);
        //        printf("replaced word:%s\n", rep_word);
        //record the used replaced word into prevusedwd
        prevUsedwd->words = realloc(
            prevUsedwd->words, (prevUsedwd->n_words + 1) * sizeof(*prevUsedwd->words));
        //copy used word and save it into category_t
        //don't forget free its memory
        prevUsedwd->words[prevUsedwd->n_words] = strdup(rep_word);
        //        printf("replace word copy:%s\n", prevUsedwd->words[prevUsedwd->n_words]);
        prevUsedwd->n_words++;
        //connect replaceword to linecopy
        repw_len = strlen(rep_word);
        linecopy = realloc(linecopy, (numcopy + repw_len + 1) * sizeof(*linecopy));
        strncat(linecopy, rep_word, repw_len);
        linecopy[numcopy + repw_len] = '\0';
        ptr_recrd = next_unds + 1;
        numcopy = numcopy + repw_len;
        if (option == 1) {
          catwd_pairs = processReuseOption(catwd_pairs, catintemp, rep_word);
          freecatarray_t(free_ptr);
          free_ptr = catwd_pairs;
        }
        free(catintemp);
      }
    }

    free(story->lineinp[i]);
    story->lineinp[i] = linecopy;
    linecopy = NULL;
    numcopy = 0;
    //printf("test line:%s", story->lineinp[i]);
  }
  if (catwd_pairs != NULL) {
    freecatarray_t(catwd_pairs);
  }
  freecategory_twords(prevUsedwd);
}

//input a line_t, free its memory//
void freeline_t(line_t * input) {
  for (size_t i = 0; i < input->num_line; i++) {
    free(input->lineinp[i]);
  }
  free(input->lineinp);
  free(input);
}

//input a category_t, free its memory//
void freecategory_twords(category_t * input) {
  for (size_t i = 0; i < input->n_words; i++) {
    free(input->words[i]);
  }
  free(input->words);
  free(input);
}

//given a string: category:word//
//save the "category" and "word" into cw_pair//
/*test cases added later*/
cw_pair * extractCategoryWords(char * inputline) {
  cw_pair * cat_word;
  cat_word = malloc(sizeof(*cat_word));
  char * colon_ptr;
  char * newline_ptr;
  size_t cat_len;
  size_t word_len;
  //generate two pointers to : and '\n'
  colon_ptr = strchr(inputline, ':');
  newline_ptr = strchr(inputline, '\n');
  if (colon_ptr == NULL) {
    fprintf(stderr, "word.txt has no :");
    exit(EXIT_FAILURE);
  }
  //compute the length of category and word
  cat_len = colon_ptr - inputline;
  word_len = newline_ptr - colon_ptr - 1;
  //  printf("catlen:%zu, wordlen:%zu\n", cat_len, word_len);
  //copy category and word
  cat_word->category = malloc((cat_len + 1) * sizeof(*cat_word->category));
  cat_word->word = malloc((word_len + 1) * sizeof(*cat_word->word));
  strncpy(cat_word->category, inputline, cat_len);
  cat_word->category[cat_len] = '\0';
  strncpy(cat_word->word, colon_ptr + 1, word_len);
  cat_word->word[word_len] = '\0';

  return cat_word;
}

//to parse the word.txt(contains category and words)//
//given a category-word file//
//generate the corresponding catarray_t//
catarray_t * parseCategoryWords(FILE * f) {
  //keep in mind that c is the output
  //when I parse the word.txt
  //the type of c is catarray_t
  catarray_t * c;
  c = malloc(sizeof(*c));
  //  c->arr = malloc(sizeof(*c->arr));
  c->arr = NULL;
  c->n = 0;
  cw_pair * catwd;
  char * line = NULL;
  size_t sz;
  while (getline(&line, &sz, f) >= 0) {
    catwd = extractCategoryWords(line);
    for (size_t i = 0; i < c->n; i++) {
      if (strcmp(catwd->category, c->arr[i].name) == 0) {
        free(catwd->category);
        c->arr[i].words =
            realloc(c->arr[i].words, (c->arr[i].n_words + 1) * sizeof(*c->arr[i].words));
        c->arr[i].words[c->arr[i].n_words] = catwd->word;
        catwd->word = NULL;
        c->arr[i].n_words++;
      }
    }
    if (catwd->word != NULL) {
      c->arr = realloc(c->arr, ((c->n) + 1) * sizeof(*c->arr));
      c->arr[c->n].n_words = 1;
      c->arr[c->n].name = catwd->category;
      catwd->category = NULL;
      c->arr[c->n].words = malloc(c->arr[c->n].n_words * sizeof(*c->arr[c->n].words));
      c->arr[c->n].words[c->arr[c->n].n_words - 1] = catwd->word;
      catwd->word = NULL;
      c->n++;
    }
    free(catwd);
  }
  free(line);
  return c;
}

void freecatarray_t(catarray_t * c) {
  for (size_t i = 0; i < c->n; i++) {
    for (size_t j = 0; j < c->arr[i].n_words; j++) {
      free(c->arr[i].words[j]);
    }
    free(c->arr[i].name);
    free(c->arr[i].words);
  }
  free(c->arr);
  free(c);
}
