#include <stdio.h>
#include <string.h>

#include "rand_story.h"

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: input story file");
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    fprintf(stderr, "cannot open file");
    return EXIT_FAILURE;
  }
  line_t * parsestory;
  parsestory = parseStory(f);
  //  check(parsestory);
  //  char * str = "_animal_";
  //char * start = strchr(str, '_');
  //char * next = strchr(start + 1, '_');
  //const char * replace;
  //replace = replaceWord(start, next);
  //printf("%s\n", replace);

  createOutputStory(parsestory, NULL, 0);
  for (size_t i = 0; i < parsestory->num_line; i++) {
    printf("%s", parsestory->lineinp[i]);
  }
  if (fclose(f) != 0) {
    perror("Failed to close the input file!");
    return EXIT_FAILURE;
  }
  freeline_t(parsestory);
  return EXIT_SUCCESS;
}