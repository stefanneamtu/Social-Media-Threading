#ifndef SOCIALMEDIATHREADING_TASK_H
#define SOCIALMEDIATHREADING_TASK_H

#include <atomic>
#include <typeinfo>

#include "Message.h"

enum Command {
    POST,
    DELETE
};

class Task {

  private:
    static std::atomic_int next_id;
    Command command;
    int id;
    Board board;
    Message message;

  public:
    Task(Command command, Message message, Board board);
    Command get_command();
    Message get_message();
    Board get_board();
    int get_id();
    int hash_code();
    bool operator==(void *other);
};

#endif //SOCIALMEDIATHREADING_TASK_H
