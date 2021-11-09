#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>

#include "function.h"
int binarySearchForZero(Function<int, int> * f, int low, int high);

class CountedIntFn : public Function<int, int> {
 protected:
  unsigned remaining;
  Function<int, int> * f;
  const char * mesg;

 public:
  CountedIntFn(unsigned n, Function<int, int> * fn, const char * m) :
      remaining(n),
      f(fn),
      mesg(m) {}
  virtual int invoke(int arg) {
    if (remaining == 0) {
      fprintf(stderr, "Too many function invocations in %s\n", mesg);
      exit(EXIT_FAILURE);
    }
    remaining--;
    return f->invoke(arg);
  }
};

class SinFunction : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return 10000000 * (sin(arg / 100000.0) - 0.5); }
};

class NegFunction : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return -3; }
};

class IncreaseFunction : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return arg + 10; }
};

class PositiveFunction : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return 10; }
};

void check(Function<int, int> * f,
           int low,
           int high,
           int expected_ans,
           const char * mesg) {
  int ans = 0;
  if (high > low) {
    ans = log(high - low) / log(2) + 1;
  }
  else {
    ans = 1;
  }

  CountedIntFn * function = new CountedIntFn(ans, f, mesg);
  int result = binarySearchForZero(function, low, high);

  if (result != expected_ans) {
    fprintf(stderr, "The expected answer is: %d, but we get: %d\n", expected_ans, result);
    exit(EXIT_FAILURE);
  }
}

int main() {
  SinFunction sin;
  NegFunction neg;
  PositiveFunction positive;
  IncreaseFunction increase;

  //f(x)=sinx
  check(&sin, 0, 150000, 52359, "sin function");

  //f(x)=-3
  check(&neg, -24, 24, 23, "check negtive in (-10, 10)");

  //f(x)=10
  //check(&positive, -10, 10, -10, "check positive in (-10, 10)");
  check(&positive, -24, 24, -24, "check positive in (-10000,1000)");

  //f(x)=x+10
  check(&increase, -24, 24, -10, "check all positive");
  exit(EXIT_SUCCESS);
}
