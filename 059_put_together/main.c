#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "counts.h"
#include "kv.h"
#include "outname.h"

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  //WRITE ME
  FILE * f = fopen(filename, "r");
  if (f == NULL) {
    perror("Could not open file");
    return NULL;
  }

  char * line = NULL;
  char * value;
  size_t sz;
  counts_t * value_counts = createCounts();
  while (getline(&line, &sz, f) >= 0) {
    line[strlen(line) - 1] = '\0';
    value = lookupValue(kvPairs, line);
    addCount(value_counts, value);
  }
  free(line);
  return value_counts;
}

int main(int argc, char ** argv) {
  //WRITE ME (plus add appropriate error checking!)
  if (argc < 3) {
    fprintf(stderr, "Usage: countfile inputFilename");
    return EXIT_FAILURE;
  }
  //read the key/value pairs from the file named by argv[1] (call the result kv)
  kvarray_t * kv;
  counts_t * c;
  char * outName;
  FILE * f;
  kv = readKVs(argv[1]);
  //count from 2 to argc (call the number you count i)
  for (int i = 2; i < argc; i++) {
    //count the values that appear in the file named by argv[i], using kv as the key/value pair
    //   (call this result c)
    c = countFile(argv[i], kv);
    //compute the output file name from argv[i] (call this outName)
    outName = computeOutputFileName(argv[i]);
    //open the file named by outName (call that f)
    f = fopen(outName, "w");
    if (f == NULL) {
      perror("Could not open file");
      return EXIT_FAILURE;
    }
    //print the counts from c into the FILE f
    printCounts(c, f);
    //close f
    if (fclose(f) != 0) {
      perror("Failed to close the input file!");
      return EXIT_FAILURE;
    }
    //free the memory for outName and c
    free(outName);
    freeCounts(c);
  }
  //free the memory for kv
  freeKVs(kv);
  return EXIT_SUCCESS;
}
