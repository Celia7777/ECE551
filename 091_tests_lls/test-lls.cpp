#include <assert.h>

#include <cstdlib>
#include <iostream>

#include "il.hpp"

class Tester {
 public:
  // testing for default constructor is done for you
  void testDefCtor() {
    IntList il;
    assert(il.head == NULL);
    assert(il.tail == NULL);
    assert(il.getSize() == 0);
  }
  // example of another method you might want to write
  void testAddFront() {
    // WRITE ME
    IntList il;
    assert(il.head == NULL);
    assert(il.tail == NULL);
    assert(il.getSize() == 0);

    il.addFront(2);
    assert(il[0] == 2);
    assert(il.head != NULL);
    assert(il.getSize() == 1);

    il.addFront(3);
    assert(il[0] == 3);
    assert(il[1] == 2);
    assert(il.getSize() == 2);
    assert(il.head->next->prev == il.head);
    assert(il.head->next == il.tail);

    il.addBack(4);
    //il: 3 2 4
    assert(il[2] == 4);
    assert(il.head->next == il.tail->prev);
  }

  void testAddBack() {
    IntList il;
    il.addBack(6);
    assert(il.head == il.tail);
  }

  void testMem() {
    IntList il;
    //il: 2 3 4
    il.addFront(3);
    il.addFront(2);
    il.addBack(4);

    IntList l1;
    l1 = il;
    assert(l1.head != il.head);

    IntList l2(il);
    IntList l3;
    //l3: 9 2 3 4
    l3.addFront(9);
    l3 = il;
  }

  void testRemove() {
    IntList il;
    il.addFront(3);

    assert(il.remove(3) == true);
    assert(il.head == NULL);

    IntList l1;
    IntList l2;
    l1.addFront(3);
    l1.addFront(2);
    l1.addFront(1);
    //l2: 1 2 3
    l2 = l1;
    assert(l2.head->next == l2.tail->prev);
    l1.remove(1);
    assert(l1.head->next == l1.tail);
    assert(l1.tail->prev == l1.head);
    //l1: 2 3
    l1[0] = 1;
    assert(l1[0] == 1 && l1[1] == 3);
    assert(l2[0] == 1 && l2[1] == 2 && l2[2] == 3);
    IntList l3;
    l3 = l2;
    l3.remove(2);
    assert(l3.head->next->next == NULL);
    assert(l3[0] == 1 && l3[1] == 3);
    assert(l3.head->next == l3.tail && l3.tail->prev == l3.head);
    assert(l3.getSize() == 2);
    assert(l3.head->prev == NULL && l3.tail->next == NULL);
    assert(l3.head->data == 1 && l3.tail->data == 3);
    assert(l3.remove(2) == false);
    l3.remove(1);
    assert(l3[0] == 3);
    assert(l3.tail == l3.head);
    assert(l3.tail->prev == NULL && l3.head->next == NULL);
    assert(l3.getSize() == 1);
    l3.remove(3);
    assert(l3.tail == NULL && l3.head == NULL);
    assert(l3.getSize() == 0);

    IntList l4;
    l4.addFront(3);
    l4.addFront(2);
    l4.addFront(1);
    assert(l4.remove(3) == true);
    assert(l4.head->next->next == NULL);
    assert(l4[0] == 1 && l4[1] == 2);
    assert(l4.head->next == l4.tail && l4.tail->prev == l4.head);
    assert(l4.getSize() == 2);
    assert(l4.head->prev == NULL && l4.tail->next == NULL);
    assert(l4.head->data == 1 && l4.tail->data == 2);
    assert(l4.remove(3) == false);
  }

  // many more tester methods
};

int main(void) {
  Tester t;
  t.testDefCtor();
  t.testAddFront();
  t.testAddBack();
  t.testMem();
  t.testRemove();
  // write calls to your other test methods here
  return EXIT_SUCCESS;
}
