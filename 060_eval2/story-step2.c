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
  catarray_t * parsewords;
  parsewords = parseCategoryWords(f);
  printWords(parsewords);
  //  cw_pair * checkpair;
  //char * input = "animal:dog\n";
  //checkpair = extractCategoryWords(input);
  //printf("category:%s\n", checkpair->category);
  //printf("name:%s\n", checkpair->word);

  if (fclose(f) != 0) {
    perror("Failed to close the input file!");
    return EXIT_FAILURE;
  }
  freecatarray_t(parsewords);
  //free(checkpair->category);
  //free(checkpair->word);
  //free(checkpair);

  return EXIT_SUCCESS;
}
