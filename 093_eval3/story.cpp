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
      page.getrank() = story.size() + 1;
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
            std::cerr << "That is not a valid choice, please try again" << std::endl;
            std::string invalinput;
            std::cin.clear();
            std::cin >> invalinput;
            if (std::cin.eof()) {
              exit(EXIT_FAILURE);
            }
            continue;
          }
          if (integer <= 0 || integer > (int)story[storypg].getNavsize()) {
            std::cerr << "That is not a valid choice, please try again" << std::endl;
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

  template<typename T>
  void findStorydepth() {
    T container;
    Page current;
    // push the page 1 into queue, the start page
    story[0].getvisited() = true;
    story[0].getdist() = 0;
    container.push(story[0]);

    while (!container.empty()) {
      current = container.front();
      container.pop();
      for (size_t i = 0; i < current.getChoices().size(); i++) {
        if (!story[current.getChoices()[i] - 1].getvisited()) {
          story[current.getChoices()[i] - 1].getvisited() = true;
          story[current.getChoices()[i] - 1].getdist() = current.getdist() + 1;
          story[current.getChoices()[i] - 1].getprev().push_back(
              std::make_pair(current.getrank(), i + 1));
          container.push(story[current.getChoices()[i] - 1]);
        }
        else if (story[current.getChoices()[i] - 1].getNavigation()[0].compare("WIN") ==
                     0 ||
                 story[current.getChoices()[i] - 1].getNavigation()[0].compare("LOSE") ==
                     0) {
          if (story[current.getChoices()[i] - 1].getprev().size() != 0) {
            story[current.getChoices()[i] - 1].getprev().push_back(
                std::make_pair(current.getrank(), i + 1));
          }
        }
      }
    }
  }

  void findPath() {
    std::stack<Page> stack;
    Page current;
    // push the page 1 into queue, the start page
    story[0].getvisited() = true;
    story[0].getdist() = 0;
    stack.push(story[0]);

    while (!stack.empty()) {
      current = stack.top();
      stack.pop();
      for (size_t i = 0; i < current.getChoices().size(); i++) {
        if (!story[current.getChoices()[i] - 1].getvisited()) {
          story[current.getChoices()[i] - 1].getvisited() = true;
          story[current.getChoices()[i] - 1].getdist() = current.getdist() + 1;

          story[current.getChoices()[i] - 1].getprev().push_back(
              std::make_pair(current.getrank(), i + 1));
          stack.push(story[current.getChoices()[i] - 1]);
        }
        else if (story[current.getChoices()[i] - 1].getNavigation()[0].compare("WIN") ==
                     0 ||
                 story[current.getChoices()[i] - 1].getNavigation()[0].compare("LOSE") ==
                     0) {
          if (story[current.getChoices()[i] - 1].getprev().size() != 0) {
            story[current.getChoices()[i] - 1].getprev().push_back(
                std::make_pair(current.getrank(), i + 1));
          }
        }
      }
    }
  }

  void findDepth() {
    std::queue<Page> queue;
    Page current;
    // push the page 1 into queue, the start page
    story[0].getvisited() = true;
    story[0].getdist() = 0;
    queue.push(story[0]);

    while (!queue.empty()) {
      current = queue.front();
      queue.pop();
      for (size_t i = 0; i < current.getChoices().size(); i++) {
        if (!story[current.getChoices()[i] - 1].getvisited()) {
          story[current.getChoices()[i] - 1].getvisited() = true;
          story[current.getChoices()[i] - 1].getdist() = current.getdist() + 1;
          queue.push(story[current.getChoices()[i] - 1]);
        }
      }
    }
  }

  void tracePath(size_t winpage, int root, std::vector<std::pair<int, int> > path) {
    //base case
    if (root == 1) {
      //call print path
      printPath(winpage, path);
    }

    //path.push_back(std::make_pair(root, -1));
    for (size_t i = 0; i < story[root - 1].getprev().size(); i++) {
      path.push_back(story[root - 1].getprev()[i]);
      //      std::cout << "push one time!" << std::endl;
      tracePath(winpage, story[root - 1].getprev()[i].first, path);
    }
  }

  void printPath(size_t winpage, std::vector<std::pair<int, int> > & path) {
    //    std::cout << "path size" << path.size() << std::endl;
    for (int i = path.size() - 1; i >= 0; i--) {
      std::cout << path[i].first << "(" << path[i].second << "),";
    }
    std::cout << winpage << "(win)" << std::endl;
  }

  void printDepth() {
    for (size_t i = 0; i < story.size(); i++) {
      if (story[i].getdist() == -1) {
        std::cout << "Page " << i + 1 << " is not reachable" << std::endl;
      }
      else {
        std::cout << "Page " << i + 1 << ":" << story[i].getdist() << std::endl;
      }
    }
    // for (size_t i = 0; i < story.size(); i++) {
    //     if (story[i].getdist() == -1) {
    //       std::cout << "Page " << i + 1 << "is not reachable." << std::endl;
    //     }
    //   }
    // }
  }
};
