#include <string.h>

#include "rand_story.h"

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: input words file");
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    fprintf(stderr, "cannot open file");
    return EXIT_FAILURE;
  }
  catarray_t * parsewords;
  //to get the catarray_t with name and words from the words file
  //which template is category:word
  parsewords = parseCategoryWords(f);
  //print the catarray_t
  printWords(parsewords);

  if (fclose(f) != 0) {
    perror("Failed to close the input file!");
    return EXIT_FAILURE;
  }
  freecatarray_t(parsewords);

  return EXIT_SUCCESS;
}
