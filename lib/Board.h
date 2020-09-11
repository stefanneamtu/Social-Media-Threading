#ifndef SOCIALMEDIATHREADING_BOARD_H
#define SOCIALMEDIATHREADING_BOARD_H

#include <set>

#include "SequentialSet.h"

class Board {

  private:
    SequentialSet<Message*> board;

  public:
    Board();
    Board(const Board& board);
    bool add_message(Message* message);
    bool delete_message(Message* message);
    int size();
    std::set<Message*> get_board_snapshot();
    bool operator==(void *other);
    bool operator==(const Board &board);
    bool operator!=(const Board &board);
    Board& operator=(const Board &board);
};

#endif //SOCIALMEDIATHREADING_BOARD_H
