#ifndef SOCIALMEDIATHREADING_SEQUENTIAL_H
#define SOCIALMEDIATHREADING_SEQUENTIAL_H

#include <atomic>
#include <utility>
#include <optional>
#include <climits>

class Task;
class Board;

template <typename E>
class SequentialSet;

#include "Node.h"
#include "Message.h"

template <typename E>
class SequentialSet {

  private:
    Node<E> *head;
    Node<E> *tail;
    std::atomic_int size;

  public:
    SequentialSet();
    std::pair<Node<E>*, Node<E>*> find(int key);
    int get_size();
    Node<E>* get_head() const;
    Node<E>* get_tail() const;
    bool contains(int key);
    bool add(E elem, int key);
    std::optional<E> remove(int key);
    SequentialSet& operator=(const SequentialSet &sq);
    bool operator==(const SequentialSet &sq);
};

template class SequentialSet<int>;
template class SequentialSet<Message>;
template class SequentialSet<Task>;
template class SequentialSet<std::pair<User, Board>>;

#include "Task.h"

#endif //SOCIALMEDIATHREADING_SEQUENTIAL_H

