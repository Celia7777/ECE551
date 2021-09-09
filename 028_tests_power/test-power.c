#include <stdio.h>
#include <stdlib.h>

unsigned power(unsigned x, unsigned y);

void run_check(unsigned x, unsigned y, unsigned expexted_ans) {
  unsigned test_value = power(x, y);
  if (test_value != expexted_ans) {
    printf("Test: %u to the %u power is %u:\n", x, y, test_value);
    exit(EXIT_FAILURE);
  }
  else {
    printf("You are right!\n");
    exit(EXIT_SUCCESS);
  }
}

int main() {
  run_check(2, 3, 8);
  run_check(2, 11, 2048);
  run_check(1, 1024, 1);
  run_check(1, 0, 1);
  run_check(0, 0, 1);
  run_check(0, 2, 0);
  run_check(-3, 2, 9);
  run_check(-3, 3, -27);

  exit(EXIT_SUCCESS);
}
