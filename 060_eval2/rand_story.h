#ifndef __RAND_STORY_H__
#define __RAND_STORY_H__

#include <stdio.h>

#include "provided.h"

//a data structure to save the output//
//after parsing the input story//
//lineinp is the array of lines//
//num_line is how many lines//
struct _line_t {
  char ** lineinp;
  size_t num_line;
};
typedef struct _line_t line_t;

//a data structure to save the category//
//and word in word.txt category:word//
struct _cw_pair_ {
  char * category;
  char * word;
};
typedef struct _cw_pair_ cw_pair;

//any functions you want your main to use

//functions for step1
line_t * parseStory(FILE * f);
const char * replaceWord(char * category, catarray_t * catg_word, category_t * usedw);
char * checkNextUnderscore(char * current_unds);
void createOutputStory(line_t * story, catarray_t * catwd_pairs, int option);
void freeline_t(line_t * input);
void checkIfhasUnderscore(line_t * story);
char * extractCategory(char * front_unds, char * back_unds);

//functions for step2
cw_pair * extractCategoryWords(char * inputline);
catarray_t * parseCategoryWords(FILE * f);
void freecatarray_t(catarray_t * c);

size_t checkIsincatarray(char * category, catarray_t * sample);
void freecategory_twords(category_t * input);

//function for step4
catarray_t * processReuseOption(catarray_t * oldcat, char * name, const char * usedword);
#endif
