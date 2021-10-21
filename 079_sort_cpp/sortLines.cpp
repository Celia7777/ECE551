#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>

template<typename T>
void printElements(T & container) {
  typename T::iterator it = container.begin();
  while (it != container.end()) {
    std::cout << *it << "\n";
    ++it;
  }
}

int main(int argc, char ** argv) {
  if (argc == 1) {
    std::vector<std::string> Vector;
    while (!std::cin.eof()) {
      std::string String;
      std::getline(std::cin, String);
      Vector.push_back(String);
    }
    std::sort(Vector.begin(), Vector.end());
    printElements<std::vector<std::string> >(Vector);
  }
  else {
    for (int i = 1; i < argc; i++) {
      std::ifstream f;
      f.open(argv[i]);
      if (f.fail()) {
        std::cerr << "failed to open this file" << std::endl;
        return EXIT_FAILURE;
      }
      std::vector<std::string> Vector;
      while (!f.eof()) {
        std::string String;
        std::getline(std::cin, String);
        Vector.push_back(String);
      }
      std::sort(Vector.begin(), Vector.end());
      printElements<std::vector<std::string> >(Vector);
      f.close();
    }
  }
  return EXIT_SUCCESS;
}
