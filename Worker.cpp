#include "Worker.h"

Worker::Worker(Backlog backlog) {
  this->backlog = backlog;
  this->interrupted = false;
}

void Worker::run() {
  while (!interrupted) {
    std::optional<Task> task_op = backlog.get_next_task();

    if (task_op) {
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
    } else {
      process(task_op);
    }
  }
}

void Worker::interrupt() {
  interrupted = true;
}

void Worker::process(Task task) {
  if (task.get_command() == POST) {
    task.get_board().add_message(task.get_message());
  } else if (!task.get_board().delete_message(task.get_message())) {
    backlog.add(Task(&task, Message(User(), std::set(), __cxx11::basic_string()), Board()));
  }
}
