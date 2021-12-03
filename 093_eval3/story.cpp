#include "story.h"

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

/*read the directory and check its filename*/
//The input is the directory name input in the command line
//and read files in this directory, check if the page file
//is valid or not, and create the story class
//if pages are valid, and no other errors
//return the number of files
int Story::readInputstory(char * directory) {
  int pagenum = 1;
  while (true) {
    Page page;
    std::ifstream f;
    std::string filename(directory);
    //append directory name to a valid page file name and read this file
    filename.append("/page");
    filename.append(std::to_string(pagenum));
    filename.append(".txt");
    f.open(filename);
    //have wrong page number (not continuous) when read file
    //so a page dose not exist, we need stop read page files
    if (!f.good()) {
      f.close();
      break;
    }
    //every time we read a valid page, create a page class
    page.pushStory(f);
    //create the rank part in the page class
    page.getrank() = story.size() + 1;
    //when we create one page, push it into the story vector
    story.push_back(page);
    pagenum++;
    f.close();
  }
  //no page1.txt
  if (story.size() == 0) {
    std::cerr << "no page1.txt" << std::endl;
    exit(EXIT_FAILURE);
  }
  return pagenum - 1;
}

/* To create a story use the story class */
//Display the current page.
//If the current page is WIN or LOSE, exit successfully.
//Otherwise, read a number from the user for their choice.
//If the input is not a number, or it is not valid for the choices on the
// 	page, prompt the user with the message
// 	and read another number. Repeat until they give a valid choice.
//Go to the page corresponding to the choice the user selected, and
//repeat the process until you exit in 5b (a WIN or a LOSE page).
bool Story::createStory() {
  int integer;
  int storypg = 0;
  int movepage;
  //print the first page
  story[0].printStory();
  while (true) {
    //check if WIN or LOSE page
    if (story[storypg].getNavigation()[0].compare("WIN") == 0 ||
        story[storypg].getNavigation()[0].compare("LOSE") == 0) {
      return true;
    }
    else {
      while (true) {
        //read the input from user
        std::cin >> integer;
        //if it is not a valid integer, remind user to input again
        //declare a string to hold the wrong input
        if (!std::cin.good()) {
          std::cout << "That is not a valid choice, please try again" << std::endl;
          std::string invalinput;
          std::cin.clear();
          std::cin >> invalinput;
          if (std::cin.eof()) {
            exit(EXIT_FAILURE);
          }
          continue;
        }
        //if the input is not between the valid choices, remind user to input again
        if (integer <= 0 || integer > (int)story[storypg].getNavsize()) {
          std::cout << "That is not a valid choice, please try again" << std::endl;
          continue;
        }
        //keep input until the user give a correct input
        break;
      }
    }
    //move to the page the user chooses
    movepage = story[storypg].getChoices()[integer - 1];
    //print this page
    story[movepage - 1].printStory();
    storypg = movepage - 1;
  }
}

/* To find a story path from page1 to winpage*/
//this is a recursive method based on DFS
//starting from page1, then iterate its neighbor pages
//and each time, recursively call the neighbor and create the path
//when we reach the win page, print that path
//the parameter findwin reference is to check if the story is unwinnable or not
void Story::findStoryPath(int start,
                          std::vector<std::pair<int, int> > path,
                          bool & findwin) {
  //base case:
  if (story[start - 1].getNavigation()[0].compare("WIN") == 0) {
    printPath(start, path);
    findwin = true;
  }
  for (size_t i = 0; i < story[start - 1].getChoices().size(); i++) {
    //everytime when we recursively call the neighbor, we need to
    //check if this neighbor is on our path or not
    if (!isinpath(story[start - 1].getChoices()[i], path)) {
      path.push_back(std::make_pair(story[start - 1].getChoices()[i], i + 1));
      findStoryPath(story[start - 1].getChoices()[i], path, findwin);
      path.pop_back();
    }
  }
}

/* helper method for the findStoryPath method*/
//to check a neighbor is on the path or not
//if is is in the path, return true; otherwise, return false
bool Story::isinpath(int currpage, std::vector<std::pair<int, int> > path) {
  for (size_t i = 0; i < path.size(); i++) {
    if (currpage == path[i].first) {
      return true;
    }
  }
  return false;
}

/* This method is to find the depth of each page starting from page1*/
//implemented by BFS
//to modify the dist and visited member in each page class
void Story::findDepth() {
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

/* print the path from page1 to winpage */
void Story::printPath(size_t winpage, std::vector<std::pair<int, int> > & path) {
  for (size_t i = 0; i < path.size() - 1; i++) {
    std::cout << path[i].first << "(" << path[i + 1].second << "),";
  }
  std::cout << winpage << "(win)" << std::endl;
}

/* print the depth of each page*/
//if it is unreachable, print it
void Story::printDepth() {
  for (size_t i = 0; i < story.size(); i++) {
    //if the distance is unchanged, it is not reachable
    if (story[i].getdist() == -1) {
      std::cout << "Page " << i + 1 << " is not reachable" << std::endl;
    }
    else {
      std::cout << "Page " << i + 1 << ":" << story[i].getdist() << std::endl;
    }
  }
}

/* get the private member */
size_t Story::getsize() const {
  return story.size();
}
std::vector<Page> Story::getstory() const {
  return story;
}
