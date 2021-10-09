#include "counts.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
counts_t * createCounts(void) {
  //WRITE ME
  counts_t * answer = malloc(sizeof(*answer));
  answer->sz = 0;
  answer->unk_count = 0;
  answer->array = NULL;
  return answer;
}
void addCount(counts_t * c, const char * name) {
  //WRITE ME
  if (name == NULL) {
    c->unk_count++;
    return;
  }

  for (size_t i = 0; i < c->sz; i++) {
    if (strcmp(c->array[i]->string, name) == 0) {
      c->array[i]->count++;
      return;
    }
  }
  c->sz++;
  c->array = realloc(c->array, c->sz * (sizeof(*c->array)));
  c->array[(c->sz) - 1] = malloc(sizeof(*c->array[c->sz - 1]));
  c->array[(c->sz) - 1]->string = name;
  c->array[(c->sz) - 1]->count = 1;
}
void printCounts(counts_t * c, FILE * outFile) {
  //WRITE ME
  for (size_t i = 0; i < c->sz; i++) {
    fprintf(outFile, "%s: %d\n", c->array[i]->string, c->array[i]->count);
  }
  if (c->unk_count > 0) {
    fprintf(outFile, "<unknown> : %d\n", c->unk_count);
  }
}

void freeCounts(counts_t * c) {
  //WRITE ME
  for (size_t i = 0; i < c->sz; i++) {
    free(c->array[i]);
  }
  free(c->array);
  free(c);
}
