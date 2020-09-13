#include "Backlog.h"

Backlog::Backlog() {}

Backlog::~Backlog() {
  //std::unique_lock<std::mutex> lock(m);
  //Node<Task*> *curr = backlog.get_head()->next;
  //while (curr != backlog.get_tail()) {
  //  Task* task = curr->elem;
  //  delete(task);
  //  curr = curr->next;
  //}
}

//Backlog::Backlog(const Backlog &backlog) {
//  std::unique_lock<std::mutex> lock(m);
//  this->backlog = backlog.backlog;
//}

int Backlog::size() {
  return backlog.get_size();
}

bool Backlog::add(Task* task){
  return backlog.add(task, task->get_id());
}

std::optional<Task*> Backlog::get_next_task(){
  return backlog.remove(backlog.get_head()->next->key);
}

int Backlog::number_of_tasks_left(){
  return backlog.get_size();
}

void Backlog::clear_backlog() {
  Node<Task*> *curr = backlog.get_head()->next;
  while (curr != backlog.get_tail()) {
    Task* task = curr->elem;
    delete(task);
    curr = curr->next;
  }
}
