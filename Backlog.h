//
// Created by stefa on 8/28/2020.
//

#ifndef SOCIALMEDIATHREADING_BACKLOG_H
#define SOCIALMEDIATHREADING_BACKLOG_H

#include "Task.h"

class Backlog {

  private:

  public:
    bool add(Task task);
    std::optional<Task> get_next_task();
    int number_of_tasks_left();
};


#endif //SOCIALMEDIATHREADING_BACKLOG_H
