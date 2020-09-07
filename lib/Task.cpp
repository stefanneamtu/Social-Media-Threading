#include "Task.h"

std::atomic_int Task::next_task_id = 0;

Task::Task(){}

Task::Task(Command command, Message message, Board *board) {
  this->command = command;
  this->message = message;
  this->board = board;
  this->id = next_task_id++;
}

Command Task::get_command() {
  return command;
}

Message Task::get_message() {
  return message;
}

Board* Task::get_board() {
  return board;
}

int Task::get_id() {
  return id;
}

int Task::hash_code() {
  return id;
}

bool Task::operator==(void *other) {

  if (this == other) {
    return true;
  }
  if (other == nullptr || typeid(this) == typeid(other)) {
    return false;
  }

  Task *task = (Task*) other;

  return id == task->get_id();
}

bool Task::operator==(Task other) {
  if (this == &other) {
    return true;
  }
  return id == other.get_id();
}
