#include "page.h"

#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <istream>
#include <vector>

//a method to parse the input story and check its #
//if the # meets the requirements of the input format
//return the line number of the #
//if not, exit error
size_t Page::findPound(std::istream & f) {
  std::string line;
  std::string::size_type position;  //record the index of # in a line
  size_t line_num = 0;              //record this is which line
  bool isfound = false;

  while (std::getline(f, line)) {
    position = line.find("#");
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

  return line_num;
}

//Input the string of each line of one page
//to check the navigation part (before #)
//check if it is WIN, LOSE or "integer:text"
//if it is WIN or LOSE, return 0
//if it is an valid integer, return this interger
//if it is not an valid interger, exit failure
int Page::checkNavigation(std::string & s) {
  std::string intstr;
  std::string::size_type colonpos;  // record the position of colon
  std::string::size_type sz;
  int integer;

  colonpos = s.find(":");
  //if the choice is WIN or CLOSE
  if (s.compare("WIN") == 0 || s.compare("LOSE") == 0) {
    return 0;
  }
  else {
    //if the choice does not have colon,
    //or the : at first, no integer
    if (colonpos == s.npos || colonpos == 0) {
      std::cerr << "no colon or the colon is at the first, thus no integer part\n";
      exit(EXIT_FAILURE);
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
      if (integer <= 0) {
        std::cerr << "the integer needs to greater than 0\n";
        exit(EXIT_FAILURE);
      }

      return integer;
    }
  }
}

//Input the page file stream, and then create the page class
//firstly check the #and the navigation part,
//if they are both valid, push the navigation, text, and
//pagechoices into the corresponding vector structure
void Page::pushStory(std::istream & f) {
  std::string line;
  size_t line_num;
  size_t line_index = 0;
  int checknav;
  //check the # is valid or not
  //and get the line which contains #
  line_num = findPound(f);
  //rewind the file stream pointer to the beginning
  f.seekg(0, f.beg);
  while (std::getline(f, line)) {
    //process the navigation part, which is before #
    if (line_index < line_num) {
      //check the navigation part is valid or not
      //and get the valid interger
      checknav = checkNavigation(line);
      if (checknav > 0) {
        //process the choices of each page
        pagechoices.push_back(checknav);
      }
      navigation.push_back(line);
    }
    //process the text part, which is after #
    if (line_index > line_num) {
      text.push_back(line);
    }
    line_index++;
  }
}

/* To print the story in the required format */
//print one page of the story
void Page::printStory() {
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
//Thie method helps to verify if one page is valid or not
//To verify:
//   1).every page that is referenced is valid, cannot be greater than the total page
//   2).every page (except page 1) is referenced by at least one
//the parameters win, lose, and intvec are all references, since
//this function is to modify their values, and then use them in main
//to check the page is valid or not
bool Page::verifyPage(int pagenum,
                      int & win,
                      int & lose,
                      std::vector<int> & intvec,
                      size_t page) {
  std::string::size_type colonpos;
  std::string::size_type sz;
  std::string intstr;
  int integer;

  for (size_t i = 0; i < navigation.size(); i++) {
    //modify the variable to verify the WIN page
    if (navigation[i].compare("WIN") == 0) {
      win++;
    }
    //modify the variable to verify the LOSE page
    else if (navigation[i].compare("LOSE") == 0) {
      lose++;
    }
    else {
      colonpos = navigation[i].find(":");
      intstr = navigation[i].substr(0, colonpos);
      integer = std::stoi(intstr, &sz);
      //the page is referenced cannot smaller or equal to 0, and cannot larger than total page
      if (integer <= 0 || integer > pagenum) {
        std::cerr << "the page referenced is invalid" << std::endl;
        exit(EXIT_FAILURE);
      }
      //modify the variable to verify the referenced choices
      //the vector of integers represent each page in a story
      //the value is the times they are references by other pages
      //so if one element is 0, which means this page(index+1) is not referenced
      else {
        if ((int)page + 1 != integer) {
          intvec[integer - 1]++;
        }
      }
    }
  }
  return true;
}

/* To get the value of the private member in the page class */
const std::vector<std::string> Page::getNavigation() const {
  return navigation;
}
const std::vector<int> Page::getChoices() const {
  return pagechoices;
}
size_t Page::getNavsize() const {
  return navigation.size();
}

/* To modify the value of the member outside of the page class */
bool & Page::getvisited() {
  return visited;
}
int & Page::getdist() {
  return dist;
}
std::vector<std::pair<int, int> > & Page::getprev() {
  return prev_rank;
}
int & Page::getrank() {
  return rank;
}
