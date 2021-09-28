#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//This function is used to figure out the ordering of the strings
//in qsort. You do not need to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}
//This function will sort data (whose length is count).
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
}

void readinputs(FILE * f) {
  char ** lines = NULL;
  char * curr = NULL;
  size_t linecap;
  size_t i = 0;
  while (getline(&curr, &linecap, f) >= 0) {
    lines = realloc(lines, (i + 1) * sizeof(*lines));
    lines[i] = curr;
    curr = NULL;
    i++;
  }
  free(curr);

  sortData(lines, i);
  for (size_t j = 0; j < i; j++) {
    printf("%s", lines[j]);
    free(lines[j]);
  }
  free(lines);
}

int main(int argc, char ** argv) {
  //WRITE YOUR CODE HERE!
  if (argc == 1) {
    readinputs(stdin);
  }
  if (argc > 1) {
    for (int i = 0; i < argc - 1; i++) {
      FILE * f = fopen(argv[i + 1], "r");
      if (f == NULL) {
        perror("Cannot open file");
        return EXIT_FAILURE;
      }
      readinputs(f);
      if (fclose(f) != 0) {
        fprintf(stderr, "Failure when close the file");
        return EXIT_FAILURE;
      }
    }
  }
  return EXIT_SUCCESS;
}
