#include "kv.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

kvpair_t * convt_kvpair(char * line) {
  char * equal_ptr = strchr(line, '=');
  assert(equal_ptr != NULL);
  size_t line_length = strlen(line);
  size_t key_length = equal_ptr - line;
  size_t value_length = line_length - key_length - 2;  //minus '='and'\n'
  kvpair_t * answer = malloc(sizeof(*answer));
  answer->key = malloc((key_length + 1) * sizeof(*answer->key));
  answer->value = malloc((value_length + 1) * sizeof(*answer->value));
  strncpy(answer->key, line, key_length);
  answer->key[key_length] = '\0';
  for (size_t i = 0; i < value_length; i++) {
    answer->value[i] = line[i + key_length + 1];
  }
  answer->value[value_length] = '\0';
  return answer;
  //free answer later
}

kvarray_t * readKVs(const char * fname) {
  //WRITE ME
  FILE * f = fopen(fname, "r");
  if (f == NULL) {
    return NULL;  //cannot open file
  }

  kvpair_t * kvpairs;
  kvarray_t * answer = malloc(sizeof(*answer));
  assert(answer != NULL);
  answer->numarr_kv = 0;
  answer->array_kv = malloc(sizeof(*answer->array_kv));
  assert(answer->array_kv != NULL);
  char * line = NULL;
  size_t sz = 0;
  while (getline(&line, &sz, f) >= 0) {
    kvpairs = convt_kvpair(line);
    answer->numarr_kv++;
    answer->array_kv =
        realloc(answer->array_kv, answer->numarr_kv * sizeof(*answer->array_kv));
    answer->array_kv[answer->numarr_kv - 1] = kvpairs;
  }
  free(line);
  //free kvpairs later
  assert(fclose(f) == 0);
  return answer;
  // free answer later
}

void freeKVs(kvarray_t * pairs) {
  //WRITE ME
  for (size_t i = 0; i < pairs->numarr_kv; i++) {
    free(pairs->array_kv[i]->key);
    free(pairs->array_kv[i]->value);
    free(pairs->array_kv[i]);
  }
  free(pairs->array_kv);
  free(pairs);
}

void printKVs(kvarray_t * pairs) {
  //WRITE ME
  for (size_t i = 0; i < pairs->numarr_kv; i++) {
    printf("key='%s' value='%s'\n", pairs->array_kv[i]->key, pairs->array_kv[i]->value);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  //WRITE ME
  for (size_t i = 0; i < pairs->numarr_kv; i++) {
    if (strcmp(key, pairs->array_kv[i]->key) == 0) {
      return pairs->array_kv[i]->value;
    }
  }
  return NULL;
}
