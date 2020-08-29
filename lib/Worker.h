#ifndef SOCIALMEDIATHREADING_WORKER_H
#define SOCIALMEDIATHREADING_WORKER_H

#include <optional>

#include "Task.h"
#include "Backlog.h"

class Worker {
  private:
    Backlog backlog;
    bool interrupted;

  public:
    Worker(Backlog backlog);
    void run();
    void interrupt();
    void process(Task next_task);
};


#endif //SOCIALMEDIATHREADING_WORKER_H
