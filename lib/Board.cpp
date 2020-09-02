#include "Board.h"
#include "Message.h"

Board::Board(){}

Board::Board(const Board &board) {
  this->board = board.board;
}

bool Board::add_message(Message message) {
  return board.add(message, message.get_id());
}

bool Board::delete_message(Message message) {
  return board.remove(message.get_id()).has_value();
}

int Board::size() {
  return board.get_size();
}

std::vector<Message> Board::get_board_snapshot() {
  std::vector<Message> snap;
  Node<Message> *curr = board.get_head()->next;
  while (curr != board.get_tail()) {
    snap.insert(snap.begin(), curr->elem);
    curr = curr->next;
  }
  return snap;
}

bool Board::operator==(void *other) {
  if (this == other) {
    return true;
  }

  if (other == nullptr || typeid(this) != typeid(other)) {
    return false;
  }

  return true; // TODO
}

bool Board::operator==(const Board &board) {
  return this->board == board.board;
}

bool Board::operator!=(const Board &board) {
  return !(*this==board);
}

Board& Board::operator=(const Board &board) {
  this->board = board.board;
  return *this;
}

