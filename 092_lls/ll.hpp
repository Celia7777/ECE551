#ifndef __LL_HPP__
#define __LL_HPP__

#include <assert.h>

#include <cstdlib>
#include <exception>

//YOUR CODE GOES HERE
class Exception : public std ::exception {
 public:
  virtual const char * what() const throw() { return "The index is out of bound"; }
};

template<typename T>
class LinkedList {
 private:
  class Node {
   public:
    T data;
    Node * next;
    Node * prev;
    Node() : data(0), next(NULL), prev(NULL) {}
    Node(T d, Node * n1, Node * n2) : data(d), next(n1), prev(n2) {}
  };
  Node * head;
  Node * tail;
  int size;

 public:
  LinkedList() : head(NULL), tail(NULL), size(0){};
  //copy constructor
  LinkedList(const LinkedList & rhs) : head(NULL), tail(NULL), size(0) {
    Node * current = rhs.head;
    while (current != NULL) {
      addBack(current->data);
      current = current->next;
    }
  }
  LinkedList & operator=(const LinkedList & rhs) {
    if (this != &rhs) {
      LinkedList temp(rhs);
      std::swap(temp.head, head);
      std::swap(temp.tail, tail);
      std::swap(temp.size, size);
    }
    return *this;
  }

  ~LinkedList() {
    while (head != NULL) {
      Node * curr = head->next;
      delete head;
      head = curr;
    }
    tail = NULL;
    size = 0;
  }

  void addFront(const T & item) {
    head = new Node(item, head, NULL);
    if (tail == NULL) {
      tail = head;
    }
    else {
      head->next->prev = head;
    }
    size++;
  }
  void addBack(const T & item) {
    tail = new Node(item, NULL, tail);
    if (head == NULL) {
      head = tail;
    }
    else {
      tail->prev->next = tail;
    }
    size++;
  }

  bool remove(const T & item) {
    if (head == NULL) {
      return false;
    }

    if (head->data == item) {
      Node * curr = head->next;
      delete head;
      head = curr;
      if (head != NULL) {
        head->prev = NULL;
      }
      else {
        tail = NULL;
      }
      size--;
      return true;
    }

    Node * current = head;
    while (current->next != NULL) {
      if (current->next->data == item) {
        if (current->next->next != NULL) {
          Node * curr = current->next->next;
          delete current->next;
          current->next = curr;
          current->next->prev = current;
        }
        else {
          delete current->next;
          tail = current;
          current->next = NULL;
        }
        size--;
        return true;
      }
      current = current->next;
    }
    return false;
  }

  T & operator[](int index) {
    if (index >= 0 && index < size) {
      Node * current = head;
      for (int i = 0; i < index; i++) {
        current = current->next;
      }
      return current->data;
    }
    else {
      throw Exception();
    }
  }

  const T & operator[](int index) const {
    if (index >= 0 && index < size) {
      Node * current = head;
      for (int i = 0; i < index; i++) {
        current = current->next;
      }
      return current->data;
    }

    else {
      throw Exception();
    }
  }

  int find(const T & item) const {
    int index = 0;
    Node * current = head;
    while (current != NULL) {
      if (current->data == item) {
        return index;
      }
      index++;
      current = current->next;
    }
    return -1;
  }

  int getSize() const { return size; }
};
#endif
