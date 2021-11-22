#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <istream>
#include <vector>

class Page {
 private:
  std::vector<std::string> navigation;
  std::vector<std::string> text;
  std::vector<int> pagechoices;
  bool visited;
  int dist;
  int prev_rank;
  int rank;

 public:
  // default constructor
  Page() : visited(false), dist(-1), prev_rank(-1), rank(-1){};
  // default destructor
  ~Page(){};

  void readOnepage(std::istream & f) {
    std::string line;
    //record the index of # in a line
    std::string::size_type pound_pos;
    //the line number which is #
    size_t pound_num = 0;
    bool haspound = false;
    //    size_t line_index = 0;
    //bool checknav = false;

    while (std::getline(f, line)) {
      pound_pos = line.find("#");
      //  std::cout << position << "\n";
      if (pound_num == 0 && pound_pos == 0) {
        std::cerr << "no navigation part, only a #\n";
        exit(EXIT_FAILURE);
      }

      //find the valid #
      if (pound_num != 0 && pound_pos == 0) {
        haspound = true;
        break;
      }
      pound_num++;
    }
    if (haspound == false) {
      std::cerr << "we cannot find a valid #\n";
      exit(EXIT_FAILURE);
    }
  }

  //a method to parse the input story and check its #
  //if the # meets the requirements of the input format
  //return the line number of the #
  //if not, exit error
  size_t findPound(std::istream & f) {
    std::string line;
    //record the index of # in a line
    std::string::size_type position;
    size_t line_num = 0;
    bool isfound = false;
    //while (!f.eof()) {
    while (std::getline(f, line)) {
      position = line.find("#");
      //  std::cout << position << "\n";
      if (line_num == 0 && position == 0) {
        std::cerr << "no navigation part, only a #\n";
        exit(EXIT_FAILURE);
      }

      //find the valid #
      if (line_num != 0 && position == 0) {
        isfound = true;
        break;
      }
      line_num++;
    }
    if (isfound == false) {
      std::cerr << "we cannot find a valid #\n";
      exit(EXIT_FAILURE);
    }
    //    std::cout << isfound << "\n";
    return line_num;
  }

  //to check the navigation part (before #)
  //check if it is WIN, LOSE or "integer:text"
  //if it is, return true; if not, return false
  int checkNavigation(std::string & s) {
    std::string intstr;
    std::string::size_type colonpos;
    std::string::size_type sz;
    int integer;

    colonpos = s.find(":");
    //if the choice is WIN or CLOSE
    if (s.compare("WIN") == 0 || s.compare("LOSE") == 0) {
      //      std::cout << "win lose\n";
      return 0;
    }
    else {
      //if the choice does not have colon,
      //or the : at first, no integer
      if (colonpos == s.npos || colonpos == 0) {
        std::cerr << "no colon or at the colon is at the first, thus no integer part\n";
        //std::cout << colonpos << "\n";
        exit(EXIT_FAILURE);  //应该是return，还是exit
      }
      //check if the integer part is valid or not
      else {
        intstr = s.substr(0, colonpos);
        for (size_t i = 0; i < colonpos; i++) {
          if (std::isdigit(intstr[i]) == 0) {
            std::cerr << "the part before colon is not invalid integer\n";
            exit(EXIT_FAILURE);
          }
        }
        integer = std::stoi(intstr, &sz);
        //pagechoices.push_back(integer);
        if (integer <= 0) {
          std::cerr << "the integer needs to greater than 0\n";
          exit(EXIT_FAILURE);
        }
        //        std::cout << "integer" << integer << std::endl;
        return integer;
        //tell if it is an integer later
      }
    }
  }

  //firstly check the # and the navigation part,
  //if they are both valid, push the navigation and text
  //into the corresponding vector structure
  void pushStory(std::istream & f) {
    std::string line;
    size_t line_num;
    size_t line_index = 0;
    int checknav;
    line_num = findPound(f);
    //    std::cout << "# at line: " << line_num << "\n";
    //rewind the file stream pointer to the beginning
    f.seekg(0, f.beg);
    while (std::getline(f, line)) {
      //std::cout << line << "-\n";
      if (line_index < line_num) {
        checknav = checkNavigation(line);
        //  std::cout << "check nav" << checknav << std::endl;
        //if (checknav == false) {
        //std::cerr << "invalid navigation part\n";
        //exit(EXIT_FAILURE);
        //}
        if (checknav > 0) {
          pagechoices.push_back(checknav);
        }

        navigation.push_back(line);
      }

      if (line_index > line_num) {
        text.push_back(line);
      }
      line_index++;
    }
    //std::cout << "int size " << pagechoices.size() << std::endl;
    //for (size_t i = 0; i < pagechoices.size(); i++) {
    //std::cout << "int in class " << pagechoices[i] << std::endl;
    //}
  }

  //print one page of the story
  void printStory() {
    std::string::size_type colonindx;
    std::string choiceinfo;
    for (size_t i = 0; i < text.size(); i++) {
      std::cout << text[i] << std::endl;
    }
    std::cout << "\n";
    if (navigation[0].compare("WIN") == 0) {
      std::cout << "Congratulations! You have won. Hooray!\n";
    }
    else if (navigation[0].compare("LOSE") == 0) {
      std::cout << "Sorry, you have lost. Better luck next time!\n";
    }
    else {
      std::cout << "What would you like to do?\n" << std::endl;
      for (size_t i = 0; i < navigation.size(); i++) {
        colonindx = navigation[i].find(":");
        choiceinfo = navigation[i].substr(colonindx + 1);
        std::cout << " " << i + 1 << ". " << choiceinfo << std::endl;
      }
    }
  }

  //verify each page, when this function is called
  //the page class is already created and the navigation
  //part has already checked valid
  bool verifyPage(int pagenum, int & win, int & lose, std::vector<int> & intvec) {
    //    std::cout << "page:" << pagenum << std::endl;
    //int winnum = 0;
    //int losenum = 0;
    std::string::size_type colonpos;
    std::string::size_type sz;
    std::string intstr;
    int integer;
    //std::vector<int> intvector;

    for (size_t i = 0; i < navigation.size(); i++) {
      //std::cout << "nav:" << navigation[i] << std::endl;
      if (navigation[i].compare("WIN") == 0) {
        win++;
        //        std::cout << "winwinwin" << std::endl;
      }
      else if (navigation[i].compare("LOSE") == 0) {
        lose++;
      }
      else {
        colonpos = navigation[i].find("#");
        intstr = navigation[i].substr(0, colonpos);
        integer = std::stoi(intstr, &sz);
        if (integer == 0 || integer > pagenum) {
          std::cerr << "the page referenced is invalid" << std::endl;
          exit(EXIT_FAILURE);
        }
        else {
          intvec[integer - 1]++;
        }
      }
      //std::cout << "integer:" << intvec[i] << std::endl;
    }

    return true;
  }

  std::vector<std::string> getNavigation() { return navigation; }
  std::vector<int> getChoices() { return pagechoices; }

  size_t getNavsize() { return navigation.size(); }
  bool & getvisited() { return visited; }
  int & getdist() { return dist; }
  int & getprev() { return prev_rank; }
  int & getrank() { return rank; }
};
