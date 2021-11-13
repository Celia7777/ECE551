#include <algorithm>
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

 public:
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
    while (!f.eof()) {
      std::getline(f, line);
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
  bool checkNavigation(std::string & s) {
    std::string integer;
    std::string::size_type colonpos;
    colonpos = s.find(":");
    //if the choice is WIN or CLOSE
    if (s.compare("WIN") == 0 || s.compare("LOSE") == 0) {
      //      std::cout << "win lose\n";
      return true;
    }
    else {
      //if the choice does not have :
      //or the : at first, no integer
      if (colonpos == s.npos || colonpos == 0) {
        std::cout << "no colon or at the first\n";
        //std::cout << colonpos << "\n";
        return false;
      }
      else {
        integer = s.substr(0, colonpos);
        //std::cout << "integer\n";
        return true;
        //tell if it is an integer later
      }
    }
  }

  void pushStory(std::istream & f) {
    std::string line;
    size_t line_num;
    size_t line_index = 0;
    bool checknav = false;
    line_num = findPound(f);
    //std::cout << "# at line: " << line_num << "\n";
    f.seekg(0, f.beg);
    while (!f.eof()) {
      std::getline(f, line);
      //std::cout << line << "-\n";

      if (line_index < line_num) {
        checknav = checkNavigation(line);
        if (checknav == false) {
          std::cerr << "invalid navigation part\n";
          exit(EXIT_FAILURE);
        }
        navigation.push_back(line);
        //        std::cout << "nav:" << navigation[line_index];
      }

      if (line_index > line_num) {
        text.push_back(line);
        //std::cout << "nav:" << text[line_index];
      }

      line_index++;
    }
  }

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
        std::cout << " " << i + 1 << ". " << choiceinfo << "\n";
      }
    }
  }
};
