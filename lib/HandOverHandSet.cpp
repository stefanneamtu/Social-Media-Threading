#include "HandOverHandSet.h"

template <typename E>
HandOverHandSet<E>::HandOverHandSet(){
  size.store(0, std::memory_order_seq_cst);
  this->tail = new Node<E>(INT_MAX, nullptr);
  this->head = new Node<E>(INT_MIN, tail);
}

template<typename E>
HandOverHandSet<E>::~HandOverHandSet() {
  Node<E>* curr = head;
  while (curr != tail) {
    Node<E>* next = curr->next;
    delete(curr);
    curr = next;
  }
  delete(tail);
}

template <typename E>
std::pair<Node<E>*, Node<E>*> HandOverHandSet<E>::find(int key) {
  Node<E> *pred = head;
  pred->m.lock();
  Node<E> *curr = pred->next;
  curr->m.lock();
  while (curr->key < key) {
    pred->m.unlock();
    pred = curr;
    curr = curr->next;
    curr->m.lock();
  }
  return std::pair<Node<E>*, Node<E>*>(pred, curr);
}

template <typename E>
int HandOverHandSet<E>::get_size() {
  return size.load(std::memory_order_seq_cst);
}

template <typename E>
Node<E>* HandOverHandSet<E>::get_head() const {
  return head;
}

template <typename E>
Node<E>* HandOverHandSet<E>::get_tail() const {
  return tail;
}

template <typename E>
bool HandOverHandSet<E>::contains(int key) {
  std::pair<Node<E>*, Node<E>*> where = find(key);
  bool ret = where.second->key == key;
  where.first->m.unlock();
  where.second->m.unlock();
  return ret;
}

template <typename E>
bool HandOverHandSet<E>::add(E elem, int key) {
  std::pair<Node<E>*, Node<E>*> where = find(key);
  bool ret = (where.second->key != key);
  if (ret) {
    Node<E> *node = new Node(elem, key);
    node->next = where.second;
    where.first->next = node;
    ++size;
  }
  where.first->m.unlock();
  where.second->m.unlock();
  return ret;
}

template <typename E>
std::optional<E> HandOverHandSet<E>::remove(int key) {
  std::pair<Node<E>*, Node<E>*> where = find(key);
  if (where.second->key != key || where.second == tail) {
    where.first->m.unlock();
    where.second->m.unlock();
    return std::nullopt;
  }
  where.first->next = where.second->next;
  --size;
  E elem = where.second->elem;
  where.first->m.unlock();
  where.second->m.unlock();
  delete(where.second);
  return elem;
}

template <typename E>
HandOverHandSet<E>& HandOverHandSet<E>::operator=(const HandOverHandSet<E> &sq) {
  this->size.store(sq.size.load(std::memory_order_seq_cst), std::memory_order_seq_cst);
  this->head = sq.get_head();
  this->tail = sq.get_tail();
  return *this;
}

template <typename E>
bool HandOverHandSet<E>::operator==(const HandOverHandSet &sq) {
  return this->head == sq.head && this->tail == sq.tail
    && this->size == sq.size;
}


