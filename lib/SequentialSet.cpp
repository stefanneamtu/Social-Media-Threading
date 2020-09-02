#include "SequentialSet.h"

template <typename E>
SequentialSet<E>::SequentialSet(){
  size = 0;
  this->tail = new Node<E>(INT_MAX, nullptr);
  this->head = new Node<E>(INT_MIN, tail);
}

template <typename E>
std::pair<Node<E>*, Node<E>*> SequentialSet<E>::find(int key) {
  Node<E> *pred;
  Node<E> *curr;
  curr = head;
  do {
    pred = curr;
    curr = curr->next;
  } while (curr->key < key);
  return std::pair<Node<E>*, Node<E>*>(pred, curr);
}

template <typename E>
int SequentialSet<E>::get_size() {
  return size;
}

template <typename E>
Node<E>* SequentialSet<E>::get_head() const {
  return head;
}

template <typename E>
Node<E>* SequentialSet<E>::get_tail() const {
  return tail;
}

template <typename E>
bool SequentialSet<E>::contains(int key) {
  return find(key).first->key == key;
}

template <typename E>
bool SequentialSet<E>::add(E elem, int key) {
  Node<E> *node = new Node(elem, key);
  std::pair<Node<E>*, Node<E>*> where = find(key);
  if (where.second->key == key) {
    return false;
  }
  node->next = where.second;
  where.first->next = node;
  ++size;
  return true;
}

template <typename E>
std::optional<E> SequentialSet<E>::remove(int key) {
  std::pair<Node<E>*, Node<E>*> where = find(key);
  if (where.second->key != key || where.second == tail) {
    return std::nullopt;
  }
  where.first->next = where.second->next;
  --size;
  return where.second->elem;
}

template <typename E>
SequentialSet<E>& SequentialSet<E>::operator=(const SequentialSet<E> &sq) {
  this->size.store(sq.size.load(std::memory_order_seq_cst), std::memory_order_seq_cst);
  this->head = sq.get_head();
  this->tail = sq.get_tail();
  return *this;
}

template <typename E>
bool SequentialSet<E>::operator==(const SequentialSet &sq) {
  return this->head == sq.head && this->tail == sq.tail
    && this->size == sq.size;
}

