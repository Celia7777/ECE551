#include "rand_story.h"

#include <ctype.h>
#include <string.h>

/*To parse the input template story*/
//given the file stream f, return a line_t//
//which contains the array of pointers, each points
// to a line of this story, and how many lines//
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

/*To check the valid category template*/
//to check if the category in "_category_" in the
//catarray_t(the output after parsing the word.txt) or not
size_t checkIsincatarray(char * category, catarray_t * sample) {
  //if category is in catarray_t or not
  //if it is, return 1; if not, return 0
  for (size_t i = 0; i < sample->n; i++) {
    if (strcmp(category, sample->arr[i].name) == 0) {
      return 1;
    }
  }
  return 0;
}

/*To check the valid integer*/
//given an extracted category from _category_
//check if it is a valid integer, if it is,
//return the exac numeric value eg "_2_", will return integer 2
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

/*To extract the category between to "_" */
//given two pointers points to the start"_" and next "_"//
//at the string "_xxx_", return xxx//
char * extractCategory(char * front_unds, char * back_unds) {
  size_t len = back_unds - front_unds - 1;  //the length of xxx
  //check if there is no words between __, just __
  if (len == 0) {
    fprintf(stderr, "there is no words between _ _\n");
    exit(EXIT_FAILURE);
  }
  char * cat_cp;
  //copy xxx into a new string
  //don't forget to free the cat_cp later
  cat_cp = strndup(front_unds + 1, len);
  return cat_cp;
}

/*To get replace word from chooseword */
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

  //if it is a valid integer of at least one
  //replace it with the previous used word
  //counting backwards from the current word
  //what if n_words<integer, not enough used words,exit failure
  if (checkinteger >= 1 && usedw->n_words >= checkinteger) {
    replaceword = usedw->words[usedw->n_words - checkinteger];
    return replaceword;
  }
  //if cat_cp is in catarray_t, return a random choice
  else if (checkcatg == 1) {
    replaceword = chooseWord(category, catg_word);
    return replaceword;
  }
  //if it is neither in catarray nor a valid integer
  else if (checkcatg == 0 && checkinteger == 0) {
    fprintf(stderr, "the category is neither in catarray nor a valid integer.\n ");
    exit(EXIT_FAILURE);
  }
  //if the integer is too large, there is not enough words
  else if (usedw->n_words < checkinteger) {
    fprintf(stderr, "the integer is too big, not enough words at the front.\n ");
    exit(EXIT_FAILURE);
  }
  else {
    return NULL;
  }
}

/*To check the next underscore */
//if I have one _ in a line, check if we have another at the back//
//if have, return a pointer to next _//
//if not, exit with error messages//
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

/*To construct a catarray_t for not reused option */
//if -n option is applied, change the old catarray_t
//remove the used word from the old catarray_t to get the new one
catarray_t * processReuseOption(catarray_t * oldcat, char * name, const char * usedword) {
  //keep in mind that c is the new catarray_t this function
  //needs to return, use c just to shorten the sentences
  catarray_t * c;
  //use flag to check when there are two same categories
  //to guarantee we can use these same words
  int flag = 0;
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
        if (strcmp(usedword, oldcat->arr[i].words[j]) != 0 || flag == 1) {
          c->arr[i].words = realloc(c->arr[i].words,
                                    (c->arr[i].n_words + 1) * sizeof(*c->arr[i].words));
          c->arr[i].words[c->arr[i].n_words] = strdup(oldcat->arr[i].words[j]);
          c->arr[i].n_words++;
        }
        else if (flag == 0) {
          flag = 1;
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

/*To create the output story based on the input template*/
//given a input line_t, modify its array of pointers to each line//
//modify _xxx_ with the corresponding replace words, eg. _animal_ into dog//
//add the option to prevent reuse word//
//if option is 0,allow reuse; if it is 1, prevent reuse//
void createOutputStory(line_t * story, catarray_t * catwd_pairs, int option) {
  //keep track of used words
  //record the previous used words in category_t
  category_t * prevUsedwd;
  prevUsedwd = malloc(sizeof(*prevUsedwd));  //remember to free at last
  prevUsedwd->n_words = 0;
  prevUsedwd->words = NULL;
  prevUsedwd->name = NULL;  //no need to use name

  char * linecopy = NULL;
  size_t numcopy = 0;
  char * ptr_recrd;
  char * next_unds;
  //the extracted category in input template
  char * catintemp;
  const char * rep_word;
  size_t repw_len;
  //use free_ptr to help free the old catarray_t
  catarray_t * free_ptr = catwd_pairs;

  //copy the characters not between _ _
  //and concatenate the replace word
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
        //check and get the next underscore
        next_unds = checkNextUnderscore(ptr_recrd);
        //get the category in _category_
        catintemp = extractCategory(ptr_recrd, next_unds);
        rep_word = replaceWord(catintemp, catwd_pairs, prevUsedwd);

        //record the used replaced word into prevusedwd
        prevUsedwd->words = realloc(
            prevUsedwd->words, (prevUsedwd->n_words + 1) * sizeof(*prevUsedwd->words));
        //copy used word and save it into category_t
        //don't forget free its memory later
        prevUsedwd->words[prevUsedwd->n_words] = strdup(rep_word);
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
          //free the old catarray
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
  }
  if (catwd_pairs != NULL) {
    freecatarray_t(catwd_pairs);
  }
  freecategory_twords(prevUsedwd);
}

/*To free the line_t */
//input a line_t, free its memory//
void freeline_t(line_t * input) {
  for (size_t i = 0; i < input->num_line; i++) {
    free(input->lineinp[i]);
  }
  free(input->lineinp);
  free(input);
}

/*To free the words in category_t */
//input a category_t, free its memory//
void freecategory_twords(category_t * input) {
  for (size_t i = 0; i < input->n_words; i++) {
    free(input->words[i]);
  }
  free(input->words);
  free(input);
}

/*To extract the category(name) and words */
//given a string: category:word//
//save the "category" and "word" into cw_pair//
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
  //copy category and word
  cat_word->category = malloc((cat_len + 1) * sizeof(*cat_word->category));
  cat_word->word = malloc((word_len + 1) * sizeof(*cat_word->word));
  strncpy(cat_word->category, inputline, cat_len);
  cat_word->category[cat_len] = '\0';
  strncpy(cat_word->word, colon_ptr + 1, word_len);
  cat_word->word[word_len] = '\0';

  return cat_word;
}

/*to parse the word.txt(contains category and words)*/
//given a category-word(eg.words.txt) file//
//generate the corresponding catarray_t//
catarray_t * parseCategoryWords(FILE * f) {
  //keep in mind that c is the output, used to just shorten the sentences
  //the type of c is catarray_t
  catarray_t * c;
  c = malloc(sizeof(*c));
  c->arr = NULL;
  c->n = 0;
  cw_pair * catwd;
  char * line = NULL;
  size_t sz;
  while (getline(&line, &sz, f) >= 0) {
    //to get one cw_pair
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

/* To free the catarray_t*/
//given a catarray_t, free its memory
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
