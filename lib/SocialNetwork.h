#ifndef SOCIALMEDIATHREADING_SOCIALNETWORK_H
#define SOCIALMEDIATHREADING_SOCIALNETWORK_H

#include <vector>
#include <set>
#include <utility>
#include <assert.h>
#include <mutex>

#include "Message.h"
#include "Board.h"
#include "Backlog.h"
class User;

class SocialNetwork {
  private:
    std::mutex m;
    Backlog *edits_backlog;
    std::vector<Board*> boards{std::vector<Board*>(10000, NULL)};
    std::vector<User*> users;

  public:
    SocialNetwork();
    SocialNetwork(Backlog *backlog);
    void register_user(User *user, Board *board);
    Message* post_message(User* sender, std::set<User*> recipients, std::string text);
    void delete_message(Message* message);
    Board* user_board(User* user);
    bool check_user_registered(User* user);
    std::vector<Board*> get_boards();
    std::vector<User*> get_users();
};

#endif //SOCIALMEDIATHREADING_SOCIALNETWORK_H
