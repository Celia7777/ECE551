#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n) {
  size_t count_length = 1;
  size_t max_length = 0;

  if (n <= 0 || array == NULL) {
    return max_length;
  }

  max_length = 1;

  for (size_t i = 0; i < n - 1; i++) {
    if (array[i + 1] > array[i]) {
      count_length++;

      if (count_length > max_length) {
        max_length = count_length;
      }
    }
    else {
      if (count_length > max_length) {
        max_length = count_length;
      }
      count_length = 1;
    }
  }
  return max_length;
}
