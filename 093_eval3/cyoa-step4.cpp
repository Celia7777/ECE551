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
    verify = story.getstory()[i].verifyPage(pagenum, winnum, losenum, intvector, i);
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
  story.findPath();
  for (size_t i = 0; i < story.getstory().size(); i++) {
    std::cout << "for page: " << i + 1 << std::endl;
    for (size_t j = 0; j < story.getstory()[i].getprev().size(); j++) {
      std::cout << "previous page " << story.getstory()[i].getprev()[j].first
                << ", from: " << story.getstory()[i].getprev()[j].second << std::endl;
    }
  }

  std::vector<std::pair<int, int> > path;
  for (size_t i = 0; i < story.getstory().size(); i++) {
    if (story.getstory()[i].getNavigation()[0].compare("WIN") == 0) {
      //   story.tracePath(i + 1, i + 1, path);
      if (story.getstory()[i].getprev().size() != 0) {
        story.tracePath(i + 1, i + 1, path);
      }
      else {
        std::cout << "This story is unwinnable!" << std::endl;
        exit(EXIT_SUCCESS);
      }
    }
  }
  return EXIT_SUCCESS;
}
