#ifndef SOCIALMEDIATHREADING_HANDOVERHAND_H
#define SOCIALMEDIATHREADING_HANDOVERHAND_H

#include <atomic>
#include <utility>
#include <optional>
#include <climits>

class Task;
class Board;

template <typename E>
class HandOverHandSet;

#include "Node.h"
#include "Message.h"

template <typename E>
class HandOverHandSet {

  private:
    Node<E> *head;
    Node<E> *tail;
    std::atomic_int size;

  public:
    HandOverHandSet();
    ~HandOverHandSet();
    std::pair<Node<E>*, Node<E>*> find(int key);
    int get_size();
    Node<E>* get_head() const;
    Node<E>* get_tail() const;
    bool contains(int key);
    bool add(E elem, int key);
    std::optional<E> remove(int key);
    HandOverHandSet& operator=(const HandOverHandSet &sq);
    bool operator==(const HandOverHandSet &sq);
};

template class HandOverHandSet<int>;
template class HandOverHandSet<Message>;
template class HandOverHandSet<Task*>;
template class HandOverHandSet<std::pair<User, Board>>;

#include "Task.h"

#endif //SOCIALMEDIATHREADING_HANDOVERHAND_H

