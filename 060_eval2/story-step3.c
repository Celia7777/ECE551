#include <stdio.h>
#include <string.h>

#include "rand_story.h"

int main(int argc, char ** argv) {
  if (argc != 3) {
    fprintf(stderr, "Usage: input story file");
    return EXIT_FAILURE;
  }
  FILE * fword = fopen(argv[1], "r");
  FILE * fstory = fopen(argv[2], "r");
  if (fword == NULL) {
    fprintf(stderr, "cannot open file about category words");
    return EXIT_FAILURE;
  }
  if (fstory == NULL) {
    fprintf(stderr, "cannot open file story template");
    return EXIT_FAILURE;
  }

  line_t * parsestory;
  catarray_t * parseword;
  //get line_t storing each lines of the input template story
  parsestory = parseStory(fstory);
  //get catarray_t storing each category name and their words
  parseword = parseCategoryWords(fword);
  //generate the ouput story and allow to reuse words
  createOutputStory(parsestory, parseword, 0);
  //print the output story
  for (size_t i = 0; i < parsestory->num_line; i++) {
    printf("%s", parsestory->lineinp[i]);
  }
  if (fclose(fword) != 0) {
    perror("Failed to close the input file!");
    return EXIT_FAILURE;
  }
  if (fclose(fstory) != 0) {
    perror("Failed to close the input file!");
    return EXIT_FAILURE;
  }
  freeline_t(parsestory);

  return EXIT_SUCCESS;
}
