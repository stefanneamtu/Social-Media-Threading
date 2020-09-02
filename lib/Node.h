#ifndef SOCIALMEDIATHREADING_NODE_H
#define SOCIALMEDIATHREADING_NODE_H

#include <mutex>

template <class E>
struct Node {
  E elem;
  int key;
  Node<E> *next;

  std::mutex m;

  explicit Node() {}
  explicit Node(int _key, Node<E> *_next) : key(_key), next(_next) {}
  explicit Node(E _elem, int _key) : elem(_elem), key(_key){}
  explicit Node(E _elem, int _key, Node<E> *_next) : elem(_elem), key(_key), next(_next){}
  explicit Node(Node<E> *_next) : next(_next){}
};

#endif //SOCIALMEDIATHREADING_NODE_H

