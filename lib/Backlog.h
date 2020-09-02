#ifndef SOCIALMEDIATHREADING_BACKLOG_H
#define SOCIALMEDIATHREADING_BACKLOG_H

#include "Task.h"
#include "SequentialSet.h"

class Backlog {

  private:
    SequentialSet<Task> backlog;

  public:
    Backlog();
    Backlog(const Backlog &backlog);
    bool add(Task task);
    std::optional<Task> get_next_task();
    int number_of_tasks_left();


};


#endif //SOCIALMEDIATHREADING_BACKLOG_H
