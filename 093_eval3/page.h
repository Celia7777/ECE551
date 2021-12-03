#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <istream>
#include <vector>

/* The is the Page class, which represents one page in a story */
// Members in this class
//  - navigation: a vector of strings to store the navigation in one page
//  - text: a vector of strings to store the text in one page
//  - pagechoices: a vector of integers to store different choices
//                 in one page, if it's not win or lose page
//  - dist: an interger to store the depth from page1 to this page

class Page {
 private:
  std::vector<std::string> navigation;
  std::vector<std::string> text;
  std::vector<int> pagechoices;
  bool visited;
  int dist;

 public:
  // default constructor
  Page() : visited(false), dist(-1){};
  // default destructor
  ~Page(){};

  void readOnepage(std::istream & f);
  size_t findPound(std::istream & f);
  int checkNavigation(std::string & s);
  void pushStory(std::istream & f);
  void printStory();
  bool verifyPage(int pagenum,
                  int & win,
                  int & lose,
                  std::vector<int> & intvec,
                  size_t page);

  const std::vector<std::string> getNavigation() const;
  const std::vector<int> getChoices() const;
  size_t getNavsize() const;

  bool & getvisited();
  int & getdist();
};
