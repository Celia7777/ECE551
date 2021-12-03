#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <istream>
#include <string>

#include "page.h"

int main(int argc, char ** argv) {
  // check command line arguments
  if (argc != 2) {
    std::cerr << "needs two command line args" << std::endl;
    return EXIT_FAILURE;
  }

  std::ifstream f;
  f.open(argv[1]);

  if (f.fail()) {
    std::cerr << "failed to open this file" << std::endl;
    return EXIT_FAILURE;
  }

  Page page;
  //create the page class
  page.pushStory(f);
  page.printStory();

  return EXIT_SUCCESS;
}
