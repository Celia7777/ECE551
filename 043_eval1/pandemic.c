#include "pandemic.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

country_t parseLine(char * line) {
  //WRITE ME

  country_t ans;
  ans.name[0] = '\0';
  ans.population = 0;

  if (strchr(line, ',') == NULL) {
    fprintf(stderr, "The input has no comma.");
    exit(EXIT_FAILURE);
  }

  int length;
  int name_length = 0;
  int popul_length;
  length = strlen(line);
  //  printf("%d\n", length);
  if (length == 0) {
    fprintf(stderr, "There is no line");
    exit(EXIT_FAILURE);
  }
  for (int i = 0; i < length; i++) {
    if (line[i] != ',') {
      name_length++;
    }
    if (line[i] == ',') {
      break;
    }
  }
  //  printf("%d\n", name_length);
  if (name_length == 0 || name_length > MAX_NAME_LEN) {
    fprintf(stderr, "There is no country name, or the name is too long");
    exit(EXIT_FAILURE);
  }
  popul_length = length - name_length - 1;
  printf("%d\n", popul_length);
  if (popul_length == 0) {
    fprintf(stderr, "There is no population info.");
    exit(EXIT_FAILURE);
  }

  char popul[popul_length];
  uint64_t popul_num;
  for (int j = 0; j < name_length; j++) {
    ans.name[j] = line[j];
  }
  ans.name[name_length] = '\0';
  for (int k = 0; k < popul_length - 1; k++) {
    popul[k] = line[length - popul_length + k];
  }
  popul_num = atoi(popul);
  ans.population = popul_num;

  return ans;
}

void calcRunningAvg(unsigned * data, size_t n_days, double * avg) {
  //WRITE ME
}

void calcCumulative(unsigned * data, size_t n_days, uint64_t pop, double * cum) {
  //WRITE ME
}

void printCountryWithMax(country_t * countries,
                         size_t n_countries,
                         unsigned ** data,
                         size_t n_days) {
  //WRITE ME
}
