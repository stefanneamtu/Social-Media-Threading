#ifndef SOCIALMEDIATHREADING_BOARD_H
#define SOCIALMEDIATHREADING_BOARD_H

#include <vector>

class Message;

class Board {

  private:

  public:
    bool add_message(Message message);
    bool delete_message(Message message);
    int size();
    std::vector<Message> get_board_snapshot();
    bool operator==(void *other);
};

#endif //SOCIALMEDIATHREADING_BOARD_H
