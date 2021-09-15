#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n);

void test_maxSeq(int * array, size_t n, int expectedlength) {
  int currentlength = maxSeq(array, n);
  if (currentlength != expectedlength) {
    printf("The answer %d is wrong.\n", currentlength);
    exit(EXIT_FAILURE);
  }
  else {
    printf("Correct answer %d!\n", currentlength);
  }
}

int main() {
  int array1[] = {0, 0, 0};
  int array2[] = {1, 2, 3, 4, 5, 6, 7, 1, 2, 1, 0, 2, 3, 4};
  int array3[] = {1, 2, 3, 1, 3, 4, 1, 3, 5};
  int array4[] = {0};
  int array5[] = {1, 2, 3, 4};
  int array6[] = {1, 1, 1, 1, 1, 1, 1, 2};
  int array7[10] = {1, 2, 3};
  int array8[] = {500, 501, 502, 503, 502, 600, 601};
  int array9[] = {-1, 0, 1};
  int array10[] = {-10, -11, -12, -13};
  int array11[] = {-10, -8, -6, -5, -2, 20};
  int array12[] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 1,
                   1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  2};

  test_maxSeq(array1, 3, 1);
  test_maxSeq(array2, 14, 7);
  test_maxSeq(array3, 9, 3);
  test_maxSeq(array4, 1, 1);
  test_maxSeq(array5, 4, 4);
  test_maxSeq(array6, 8, 2);
  test_maxSeq(array7, 10, 3);
  test_maxSeq(array8, 7, 4);
  test_maxSeq(array9, 3, 3);
  test_maxSeq(array10, 4, 1);
  test_maxSeq(array11, 6, 6);
  test_maxSeq(array12, 24, 2);
  test_maxSeq(NULL, 0, 0);

  return EXIT_SUCCESS;
}
