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
  //obtain the line_t which contains each line of the input story
  //and how many lines of this story
  parsestory = parseStory(f);
  //replace each xxx in _xxx_ with the replace word produced by chooseword
  createOutputStory(parsestory, NULL, 0);
  //print the output story
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
