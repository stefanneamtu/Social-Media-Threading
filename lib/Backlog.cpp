#include "Backlog.h"

Backlog::Backlog() {
  this->backlog = SequentialSet<Task>();
}

Backlog::Backlog(const Backlog &backlog) {
  this->backlog = backlog.backlog;
}

bool Backlog::add(Task task){
  return backlog.add(task, task.get_id());
}

std::optional<Task> Backlog::get_next_task(){
  return backlog.remove(backlog.get_head()->next->key);
}

int Backlog::number_of_tasks_left(){
  return backlog.get_size();
}

