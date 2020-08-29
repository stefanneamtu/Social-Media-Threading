#ifndef SOCIALMEDIATHREADING_SOCIALNETWORK_H
#define SOCIALMEDIATHREADING_SOCIALNETWORK_H

#include <vector>
#include <set>
#include <utility>
#include <assert.h>

#include "Message.h"
#include "Backlog.h"
#include "Board.h"

class SocialNetwork {
  private:
    Backlog edits_backlog;
    std::atomic<std::vector<Board>> boards;
    std::atomic<std::vector<User>> users;

  public:
    SocialNetwork(Backlog edits_backlog);
    void register_user(User user, Board board);
    Message post_message(User sender, std::set<User> recipients, std::string text);
    void delete_message(Message message);
    Board user_board(User user);
    void check_user_registered(User user);
    std::vector<Board> get_boards();
    std::vector<User> get_users();
};

#endif //SOCIALMEDIATHREADING_SOCIALNETWORK_H
