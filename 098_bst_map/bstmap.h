#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <stdexcept>

#include "map.h"

template<typename K, typename V>
class BstMap : public Map<K, V> {
 private:
  class Node {
   public:
    K key;
    V value;
    Node * left;
    Node * right;
    Node() : key(0), value(0), left(NULL), right(NULL) {}
    Node(K key, V value) : key(key), value(value), left(NULL), right(NULL) {}
  };
  Node * root;

 public:
  BstMap<K, V>() : root(NULL) {}
  //copy constructor
  BstMap(const BstMap & rhs) : root(NULL) { root = copyconstruct(rhs.root); }

  Node * copyconstruct(Node * current) {
    if (current == NULL) {
      return NULL;
    }
    Node * copy = new Node(current->key, current->value);
    copy->left = copyconstruct(current->left);
    copy->right = copyconstruct(current->right);
    return copy;
  }

  //assignment operator
  BstMap & operator=(const BstMap & rhs) {
    if (this != &rhs) {
      destroy(root);
      root = copyconstruct(rhs.root);
    }
    return *this;
  }
  //destructor
  ~BstMap<K, V>() { destroy(root); }

  void destroy(Node * current) {
    if (current != NULL) {
      destroy(current->left);
      destroy(current->right);
      delete current;
    }
  }

  virtual void add(const K & key, const V & value) {
    Node ** current = &root;
    while (*current != NULL) {
      if ((*current)->key == key) {
        (*current)->value = value;
        return;
      }
      else if ((*current)->key < key) {
        current = &((*current)->right);
      }
      else {
        current = &((*current)->left);
      }
    }
    *current = new Node(key, value);
  }

  virtual const V & lookup(const K & key) const throw(std::invalid_argument) {
    Node * current = root;
    while (current != NULL) {
      if (current->key == key) {
        return current->value;
      }
      else if (current->key < key) {
        current = current->right;
      }
      else {
        current = current->left;
      }
    }
    throw std::invalid_argument("Don't find key!!\n");
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
          (*current)->value = (*temp)->value;
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
      std::cout << current->key << " : " << current->value << "\n";
      printer(current->right);
    }
  }

  void Printmap() {
    printer(root);
    std::cout << std::endl;
  }
};
