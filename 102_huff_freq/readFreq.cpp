#include "readFreq.h"

#include <stdio.h>

#include <cstdlib>
#include <fstream>

void printSym(std::ostream & s, unsigned sym) {
  if (sym > 256) {
    s << "INV";
  }
  else if (sym == 256) {
    s << "EOF";
  }
  else if (isprint(sym)) {
    char c = sym;
    s << "'" << c << "'";
  }
  else {
    std::streamsize w = s.width(3);
    s << std::hex << sym << std::dec;
    s.width(w);
  }
}
uint64_t * readFrequencies(const char * fname) {
  //WRITE ME!
  std::ifstream f;
  f.open(fname);
  if (f.fail()) {
    std::cerr << "cannot open the file" << std::endl;
    exit(EXIT_FAILURE);
  }
  uint64_t * freqarr;
  freqarr = new uint64_t[257]();

  int c = 0;
  while ((c = f.get()) != EOF) {
    freqarr[c]++;
  }
  freqarr[256] = 1;
  f.close();
  return freqarr;
}
