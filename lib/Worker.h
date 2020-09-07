#ifndef SOCIALMEDIATHREADING_WORKER_H
#define SOCIALMEDIATHREADING_WORKER_H

#include <optional>
#include <pthread.h>
#include <thread>

#include "Task.h"
#include "Backlog.h"

class Worker {
  private:
    Backlog *backlog;
    bool interrupted;
    std::thread thr;

  public:
    Worker();
    Worker(Backlog *backlog);
    void run();
    void interrupt();
    void process(Task *next_task);
    void start();
    void join();
};


#endif //SOCIALMEDIATHREADING_WORKER_H
