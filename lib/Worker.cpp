#include "Worker.h"

Worker::Worker(){}

Worker::Worker(Backlog *backlog) {
  this->backlog = backlog;
  this->interrupted = false;
}

Worker::Worker(const Worker &worker) {
  this->backlog = worker.backlog;
  this->interrupted = worker.interrupted;
}

void Worker::run() {
  while (!interrupted) {
    std::optional<Task*> task_op = backlog->get_next_task();

    if (!task_op.has_value()) {
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
    } else {
      process(task_op.value());
    }
  }
}

void Worker::interrupt() {
  interrupted = true;
}

void Worker::process(Task *task) {
  if (task->get_command() == POST) {
    task->get_board()->add_message(task->get_message());
  } else if (task->get_board()->delete_message(task->get_message())) {
    //delete(task->get_message());
  } else {
    backlog->add(new Task(task->get_command(), task->get_message(), task->get_board()));
  }
  delete(task);
}

void Worker::start() {
  thr = std::thread(&Worker::run, this);
}

void Worker::join() {
  thr.join();
}
