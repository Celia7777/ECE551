#include <stdio.h>
#include <string.h>

#include "rand_story.h"

int main(int argc, char ** argv) {
  FILE * fword;
  FILE * fstory;
  int option;

  if (argc == 3) {
    fword = fopen(argv[1], "r");
    fstory = fopen(argv[2], "r");
    option = 0;
  }

  else if (argc == 4) {
    //if we type "-n" at the command line reusing words is not allowed
    if (strcmp(argv[1], "-n") == 0) {
      option = 1;
    }
    else {
      fprintf(stderr, "Only accept -n option");
      return EXIT_FAILURE;
    }
    fword = fopen(argv[2], "r");
    fstory = fopen(argv[3], "r");
  }
  else {
    fprintf(stderr, "Usage: input story file and word file");
    return EXIT_FAILURE;
  }

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
  parsestory = parseStory(fstory);
  parseword = parseCategoryWords(fword);
  //add the parameter option, if it is 1, prevent using reused words
  //if it is 0, allow to use reused words
  createOutputStory(parsestory, parseword, option);
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
