#include <cstdio>
#include <cstdlib>
#include <iostream>

#include "bstset.h"

int main() {
  BstSet<int> set;
  set.add(77);
  set.add(17);
  set.add(57);
  set.add(0);
  set.add(27);
  set.add(-1);
  set.add(32);
  set.add(7);
  set.add(11);
  set.Printset();
  bool ans1 = set.lookup(17);
  bool ans2 = set.lookup(111);
  set.remove(10);
  std::cout << "ans1 should be true and =" << ans1 << "\n";
  std::cout << "ans2 should be false and =" << ans2 << "\n";
  set.remove(-1);
  set.Printset();

  BstSet<int> setcp(set);
  setcp.inOrderPrint();

  return EXIT_SUCCESS;
}
