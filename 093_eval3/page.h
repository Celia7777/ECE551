#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <istream>
#include <vector>

/* */
class Page {
 private:
  std::vector<std::string> navigation;
  std::vector<std::string> text;
  std::vector<int> pagechoices;
  bool visited;
  int dist;
  std::vector<std::pair<int, int> > prev_rank;
  int rank;

 public:
  // default constructor
  Page() : visited(false), dist(-1), rank(-1){};
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
  std::vector<std::pair<int, int> > & getprev();
  int & getrank();
};
