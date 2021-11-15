#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <istream>
#include <vector>

#include "page.cpp"

class Story {
 private:
  std::vector<Page> story;

 public:
  //read the directory and check its filename
  //return the number of files
  int readInputstory(char * directory) {
    int pagenum = 1;
    // std::ifstream f;

    while (true) {
      Page page;
      std::ifstream f;
      std::string filename(directory);
      //std::cout << filename << std::endl;
      filename.append("/page");
      //std::cout << filename << std::endl;
      filename.append(std::to_string(pagenum));
      //std::cout << filename << std::endl;
      filename.append(".txt");
      //std::cout << filename << std::endl;

      f.open(filename);
      //if (f.fail()) {
      // std::cerr << "failed to open this file" << std::endl;
      // exit(EXIT_FAILURE);
      //}
      //have wrong page number (not continuous) when read file
      //so a page dose not exist, we need stop read page files

      if (!f.good()) {
        //        std::cout << "here!" << std::endl;
        break;  //???
      }
      page.pushStory(f);
      //      page.printStory();
      story.push_back(page);

      pagenum++;
    }

    //no page1.txt
    if (story.size() == 0) {
      std::cerr << "no page1.txt" << std::endl;
      exit(EXIT_FAILURE);
    }
    return pagenum - 1;
  }

  //void printStory() {
  //for (size_t i = 0; i < story.size(); i++) {
  //  story[i].printStory();
  //}
  //}

  size_t getsize() { return story.size(); }
  std::vector<Page> getstory() { return story; }

  void createStory() {
    int integer;
    int storypg = 0;
    int movepage;
    story[0].printStory();
    while (true) {
      //check if WIN or LOSE page
      if (story[storypg].getNavigation()[0].compare("WIN") == 0 ||
          story[storypg].getNavigation()[0].compare("LOSE") == 0) {
        exit(EXIT_SUCCESS);
      }

      else {
        while (true) {
          std::cin >> integer;
          if (!std::cin.good()) {
            std::cerr << "Please input an valid integer" << std::endl;
            continue;
          }
          if (integer <= 0 || integer > (int)story[storypg].getNavsize()) {
            std::cerr << "Please input an integer between 0 and "
                      << story[storypg].getNavsize() << std::endl;
            continue;
          }
          break;
        }
      }
      movepage = story[storypg].getChoices()[integer - 1];
      //      std::cout << "move page" << movepage << std::endl;
      story[movepage - 1].printStory();
      //for (size_t j = 0; j < story[i].getNavsize(); j++) {
      //check if WIN or LOSE page
      //if (story[i].getNavigation()[j].compare("WIN") == 0 ||
      //  story[i].getNavigation()[j].compare("LOSE") == 0) {
      //  exit(EXIT_SUCCESS);
      //}
      storypg = movepage - 1;
    }
  }
};
