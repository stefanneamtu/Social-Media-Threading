#include "Board.h"
#include "Message.h"

Board::Board(){}

Board::~Board() {
  //std::unique_lock<std::mutex> lock(m);
  //Node<Message*> *curr = board.get_head()->next;
  //while (curr != board.get_tail()) {
  //  Message *message = curr->elem;
  //  delete(message);
  //  curr = curr->next;
  //}
}

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

std::set<Message> Board::get_board_snapshot() {
  std::set<Message> snap;
  Node<Message> *curr = board.get_head()->next;
  while (curr != board.get_tail()) {
    snap.insert(curr->elem);
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

void Board::clear_board() {
  //Node<Message> *curr = board.get_head()->next;
  //while (curr != board.get_tail()) {
  //  Message *message = curr->elem;
  //  delete(message);
  //  curr = curr->next;
  //}
}

