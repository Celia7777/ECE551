#ifndef __COUNTS_H__
#define __COUNTS_H__

#include <stdio.h>

struct _one_count_t {
  //DEFINE ME
  const char * string;
  int count;
};
typedef struct _one_count_t one_count_t;

struct _counts_t {
  //DEFINE ME
  one_count_t ** array;
  size_t sz;
  int unk_count;
};
typedef struct _counts_t counts_t;

counts_t * createCounts(void);
void addCount(counts_t * c, const char * name);
void printCounts(counts_t * c, FILE * outFile);

void freeCounts(counts_t * c);

#endif
