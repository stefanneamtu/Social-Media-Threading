#ifndef SOCIALMEDIATHREADING_BACKLOG_H
#define SOCIALMEDIATHREADING_BACKLOG_H

#include <thread>
#include <mutex>

#include "Task.h"
//#include "SequentialSet.h"
#include "HandOverHandSet.h"

class Backlog {

  private:
    std::mutex m;
    HandOverHandSet<Task*> backlog;

  public:
    Backlog();
    ~Backlog();
    //Backlog(const Backlog &backlog);
    int size();
    bool add(Task* task);
    std::optional<Task*> get_next_task();
    int number_of_tasks_left();
    void clear_backlog();


};


#endif //SOCIALMEDIATHREADING_BACKLOG_H
