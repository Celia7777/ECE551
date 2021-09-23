#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

void frequency_count(FILE * f, int * array) {
  int c;
  while ((c = fgetc(f) != EOF)) {
    if (isalpha(c)) {
      c = tolower(c);
      array[c - 'a']++;
    }
  }
}
int determine_e(int * array, int size) {
  int index = 0;
  int current_e = array[0];

  for (int i = 0; i < size - 1; i++) {
    if (array[i + 1] > current_e) {
      current_e = array[i + 1];
      index = i + 1;
    }
  }
  return index;
}

int solve_key(FILE * f) {
  int e_index;
  int key;
  int letter[26] = {0};
  frequency_count(f, letter);
  e_index = determine_e(letter, 26);
  if (e_index >= 4) {
    key = e_index - 4;
  }
  else {
    key = 22 + e_index;
  }
  printf("%d\n", key);
  return key;
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: encrypt key inputFilename");
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("Could not open file");
    return EXIT_FAILURE;
  }
  solve_key(f);
  if (fclose(f) != 0) {
    perror("Failed to close the input file!");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
