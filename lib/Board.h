#ifndef SOCIALMEDIATHREADING_BOARD_H
#define SOCIALMEDIATHREADING_BOARD_H

#include <set>
#include <thread>
#include <mutex>

#include "SequentialSet.h"

class Board {

  private:
    std::mutex m;
    SequentialSet<Message> board;

  public:
    Board();
    ~Board();
    Board(const Board& board);
    bool add_message(Message message);
    bool delete_message(Message message);
    int size();
    std::set<Message> get_board_snapshot();
    bool operator==(void *other);
    bool operator==(const Board &board);
    bool operator!=(const Board &board);
    Board& operator=(const Board &board);
    void clear_board();
};

#endif //SOCIALMEDIATHREADING_BOARD_H
