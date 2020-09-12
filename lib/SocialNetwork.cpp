#include "SocialNetwork.h"

SocialNetwork::SocialNetwork() {}

SocialNetwork::SocialNetwork(Backlog *backlog) {
  this->edits_backlog = backlog;
}

void SocialNetwork::register_user(User* user, Board *board) {
  std::unique_lock<std::mutex> lock(m);
  boards[user->hash_code()] = board;
  users.push_back(user);
}

Message* SocialNetwork::post_message(User* sender, std::set<User*> recipients, std::string text) {
  check_user_registered(std::move(sender));
  assert(!recipients.count(sender));

  Message* message = new Message(sender, recipients, text);

  std::set<User*> all_recipients(recipients);
  all_recipients.insert(sender);

  for (User* user : all_recipients) {
    check_user_registered(user);
    Task *add = new Task(POST, message, boards[user->hash_code()]);
    if (!edits_backlog->add(add)) {
      delete(add);
    }
  }
  return message;
}

void SocialNetwork::delete_message(Message* message) {
  for (long unsigned int i = 0; i < users.size(); ++i) {
    if (message->get_recipients().count(users[i]) || message->get_sender() == users[i]) {
      Task *add = new Task(DELETE, message, boards[i]);
      if (!edits_backlog->add(add)) {
        delete(add);
      }
    }
  }
}

Board* SocialNetwork::user_board(User* user) {
  return boards[user->hash_code()];
}

bool SocialNetwork::check_user_registered(User* user) {
  std::unique_lock<std::mutex> lock(m);
  return boards[user->hash_code()] != NULL;
}

std::vector<Board*> SocialNetwork::get_boards() {
  return boards;
}

std::vector<User*> SocialNetwork::get_users() {
  std::unique_lock<std::mutex> lock(m);
  return users;
}
