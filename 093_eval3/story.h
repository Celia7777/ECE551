#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <istream>
#include <queue>
#include <stack>
#include <utility>
#include <vector>

#include "page.h"

/* This is the story class to represent a story */
// The member in story is a vector of pages
class Story {
 private:
  std::vector<Page> story;

 public:
  //default destructor
  ~Story(){};

  int readInputstory(char * directory);
  bool createStory();
  void findDepth();
  void printDepth();
  //helper method for findStoryPath
  bool isinpath(int currpage, std::vector<std::pair<int, int> > path);
  void findStoryPath(int start, std::vector<std::pair<int, int> > path, bool & findwin);
  void printPath(size_t winpage, std::vector<std::pair<int, int> > & path);

  //To read the private field outside of the class
  size_t getsize() const;
  std::vector<Page> getstory() const;
};
