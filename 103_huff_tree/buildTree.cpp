#include "node.h"

Node * buildTree(uint64_t * counts) {
  //WRITE ME!

  priority_queue_t pq;
  for (size_t i = 0; i < 257; i++) {
    if (counts[i] != 0) {
      pq.push(new Node(i, counts[i]));
    }
  }
  if (pq.empty()) {
    return NULL;
  }

  while (pq.size() > 1) {
    Node * l = pq.top();
    pq.pop();
    Node * r = pq.top();
    pq.pop();
    Node * tree = new Node(l, r);
    pq.push(tree);
  }
  return pq.top();
}
