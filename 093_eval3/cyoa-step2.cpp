#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <istream>
#include <string>

#include "story.cpp"

int main(int argc, char ** argv) {
  // check command line arguments
  if (argc != 2) {
    std::cerr << "needs two command line args" << std::endl;
    return EXIT_FAILURE;
  }

  Story story;
  int pagenum;
  pagenum = story.readInputstory(argv[1]);
  bool verify;
  int winnum = 0;
  int losenum = 0;
  std::vector<int> intvector;
  for (int i = 0; i < pagenum; i++) {
    intvector.push_back(0);
    //    std::cout << "originalint:" << intvector[i] << std::endl;
  }
  //  story.printStory();
  //std::cout << "story size" << story.getsize() << std::endl;
  for (size_t i = 0; i < story.getsize(); i++) {
    verify = story.getstory()[i].verifyPage(pagenum, winnum, losenum, intvector);
  }
  //check WIN
  if (winnum == 0) {
    std::cerr << "no WIN choice" << std::endl;
    exit(EXIT_FAILURE);
  }

  //check LOSE
  if (losenum == 0) {
    std::cerr << "no LOSE choice" << std::endl;
    exit(EXIT_FAILURE);
  }
  //check reference time
  for (int i = 0; i < pagenum; i++) {
    if (intvector[i] == 0 && i != 0) {
      std::cerr << "every page needs to be referenced at least once" << std::endl;
      exit(EXIT_FAILURE);
    }
  }
  story.createStory();
  //std::cout << verify << std::endl;
  return EXIT_SUCCESS;
}
