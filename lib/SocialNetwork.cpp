#include "SocialNetwork.h"

SocialNetwork::SocialNetwork() {}

SocialNetwork::SocialNetwork(Backlog backlog) {
  this->backlog = backlog;
}

void SocialNetwork::register_user(User user, Board *board) {
  boards[user.hash_code()] = board;
  users.push_back(user);
}

Message SocialNetwork::post_message(User sender, std::set<User> recipients, std::string text, Backlog *edits_backlog) {
  check_user_registered(std::move(sender));
  assert(!recipients.count(sender));

  Message message = Message(std::move(sender), recipients, text);

  std::set<User> all_recipients(recipients);
  all_recipients.insert(sender);

  for (User user : all_recipients) {
    check_user_registered(user);
    edits_backlog->add(Task(POST, message, boards[user.hash_code()]));
  }
  return message;
}

void SocialNetwork::delete_message(Message message, Backlog *edits_backlog) {
  for (long unsigned int i = 0; i < users.size(); ++i) {
    if (message.get_recipients().count(users[i]) || message.get_sender() == users[i]) {
      edits_backlog->add(Task(DELETE, message, boards[i]));
    }
  }
}

Board* SocialNetwork::user_board(User user) {
  return boards[user.hash_code()];
}

bool SocialNetwork::check_user_registered(User user) {
  return boards[user.hash_code()] != NULL;
}

std::vector<Board*> SocialNetwork::get_boards() {
  return boards;
}

std::vector<User> SocialNetwork::get_users() {
  return users;
}
