#include <cmath>
#include <cstdlib>

#include "function.h"

int binarySearchForZero(Function<int, int> * f, int low, int high) {
  while ((high - low) > 1) {
    int mid = (high - low) / 2 + low;
    int func = f->invoke(mid);
    if (func > 0) {
      high = mid;
    }
    else if (func < 0) {
      low = mid;
    }
    else {
      return mid;
    }
  }
  return low;
}
