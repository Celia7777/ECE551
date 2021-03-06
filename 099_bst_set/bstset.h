#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <stdexcept>

#include "set.h"

template<typename K>
class BstSet : public Set<K> {
 private:
  class Node {
   public:
    K key;
    Node * left;
    Node * right;
    Node() : key(0), left(NULL), right(NULL) {}
    Node(K k) : key(k), left(NULL), right(NULL) {}
  };
  Node * root;

 public:
  BstSet<K>() : root(NULL) {}
  //copy constructor
  BstSet(const BstSet & rhs) : root(NULL) { root = copyconstruct(rhs.root); }
  Node * copyconstruct(Node * current) {
    if (current == NULL) {
      return NULL;
    }
    Node * copy = new Node(current->key);
    copy->left = copyconstruct(current->left);
    copy->right = copyconstruct(current->right);
    return copy;
  }

  //assignment operator
  BstSet & operator=(const BstSet & rhs) {
    if (this != &rhs) {
      destroy(root);
      root = copyconstruct(rhs.root);
    }
    return *this;
  }
  //destructor
  ~BstSet<K>() { destroy(root); }

  void destroy(Node * current) {
    if (current != NULL) {
      destroy(current->left);
      destroy(current->right);
      delete current;
    }
  }

  virtual void add(const K & key) {
    Node ** current = &root;
    while (*current != NULL) {
      if ((*current)->key == key) {
        return;
      }
      else if ((*current)->key < key) {
        current = &((*current)->right);
      }
      else {
        current = &((*current)->left);
      }
    }
    *current = new Node(key);
  }

  virtual bool contains(const K & key) const {
    Node * current = root;
    while (current != NULL) {
      if (current->key == key) {
        return true;
      }
      else if (current->key < key) {
        current = current->right;
      }
      else {
        current = current->left;
      }
    }
    return false;
  }

  virtual void remove(const K & key) {
    Node ** current = &root;
    Node * curr = NULL;
    while (*current != NULL) {
      if ((*current)->key == key) {
        //check child
        if ((*current)->left == NULL) {
          curr = (*current)->right;
          delete *current;
          (*current) = curr;
        }
        else if ((*current)->right == NULL) {
          curr = (*current)->left;
          delete *current;
          (*current) = curr;
        }
        else {
          Node ** temp = current;
          temp = &(*current)->left;
          while ((*temp)->right != NULL) {
            temp = &(*temp)->right;
          }
          (*current)->key = (*temp)->key;
          curr = (*temp)->left;
          delete (*temp);
          *temp = curr;
        }
      }
      else if ((*current)->key < key) {
        current = &(*current)->right;
      }
      else {
        current = &(*current)->left;
      }
    }
  }

  void printer(Node * current) {
    if (current != NULL) {
      printer(current->left);
      std::cout << "key:" << current->key << "\n";
      printer(current->right);
    }
  }

  void Printset() {
    printer(root);
    std::cout << std::endl;
  }
};
