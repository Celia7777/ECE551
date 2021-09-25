#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void rotate_matrix(FILE * f) {
  char input_line[12];
  char rotated_matrix[10][10];
  int line_num = 0;

  for (int i = 0; i < 10; i++) {
    if (fgets(input_line, 12, f) != NULL) {
      if (input_line[10] != '\n') {
        fprintf(stderr, "The line in the input file has wrong size.");
        exit(EXIT_FAILURE);
      }
      //    if (strchr(input_line, '\n') == NULL) {
      //fprintf(stderr, "The line in the input file is more than 11 char.");
      //exit(EXIT_FAILURE);
      //}
      if (strlen(input_line) < 11) {
        fprintf(stderr, "The line contain less than 10 char");
        exit(EXIT_FAILURE);
      }
      //         if (input_line[0] == '\n') {
      //fprintf(stderr, "The size of lines is incorrect.");
      //exit(EXIT_FAILURE);
      //}
      else {
        for (int j = 0; j < 10; j++) {
          rotated_matrix[j][9 - i] = input_line[j];
        }
      }
      line_num++;
    }
  }
  if (line_num < 10) {
    fprintf(stderr, "The size of lines is incorrect.");
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      printf("%c", rotated_matrix[i][j]);
    }
    printf("%c", '\n');
  }
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: rotate matrix inputFilename");
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("Could not open file");
    return EXIT_FAILURE;
  }
  rotate_matrix(f);
  if (fclose(f) != 0) {
    perror("Failed to close the input file!");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
