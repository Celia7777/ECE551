#include "outname.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * computeOutputFileName(const char * inputName) {
  //WRITE ME
  size_t input_len = strlen(inputName);
  char * answer = malloc((input_len + 8) * sizeof(answer));
  strcpy(answer, inputName);
  strcat(answer, ".counts");
  return answer;
}
