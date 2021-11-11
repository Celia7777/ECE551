#include <cstdio>
#include <cstdlib>
#include <iostream>

#include "bstmap.h"

int main() {
  BstMap<int, int> map;
  map.add(77, 1);
  map.add(17, 2);
  map.add(57, 3);
  map.add(0, 4);
  map.add(27, 5);
  map.add(-1, 6);
  map.add(32, 7);
  map.add(7, 8);
  map.add(11, 9);
  map.Printmap();
  int ans1 = map.lookup(17);
  int ans2 = map.lookup(11);
  map.remove(10);
  std::cout << "ans1 should be 2 and =" << ans1 << "\n";
  std::cout << "ans2 should be 9 and =" << ans2 << "\n";

  BstMap<int, int> mapnew = map;
  mapnew.Printmap();
  return EXIT_SUCCESS;
}
