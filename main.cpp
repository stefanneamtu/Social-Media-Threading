#include <iostream>
#include <mutex>

#include "Message.h"
#include "Task.h"
#include "SocialNetwork.h"
#include "Worker.h"
#include "User.h"
#include "Backlog.h"
#include "Board.h"
#include "Node.h"
#include "SequentialSet.h"

void user_tests() {
  User("User0");
  User("User1");
  User("User2");
  User user = User("User3");

  if (user.get_id() != 3) {
    std::cout << "User id test failed!\n";
    return;
  }

  if (user.get_name() != "User3") {
    std::cout << "User name test failed!\n";
    return;
  }

  if (User("User4") < user) {
    std::cout << "User comparison test failed!\n";
    return;
  }

  User user_clone = user;
  User user_clone2(user);

  if (user == user_clone && user == user && user == user_clone2) {
    std::cout << "User tests passed!\n";
  } else {
    std::cout << "User clone test failed!\n";
  }
}

void worker_tests() {
}

void message_tests() {
  User sender = User("Sender");
  std::set<User> recipients;
  for (int i = 0; i < 5; ++i) {
    recipients.insert(User("Recipient"));
  }

  Message(sender, recipients, "Message0");
  Message(sender, recipients, "Message1");
  Message(sender, recipients, "Message2");
  Message(sender, recipients, "Message3");

  Message message = Message(sender, recipients, "Message4");

  if (message.get_id() != 4) {
    std::cout << "Message id test failed!\n";
    return;
  }

  if (message.get_text() != "Message4") {
    std::cout << "Message text test failed!\n";
    return;
  }

  Message message_clone = message;
  Message message_clone2(message);

  if ((message == message_clone && message == message && message == message_clone2) ||
      (message == &message_clone && message == &message && message == &message_clone2)) {
    std::cout << "Message tests passed!\n";
  } else {
    std::cout << "Message clone test failed!\n";
  }
}

void task_tests() {
  Message message;
  Command command = POST;
  Board board;
  Task(command, message, &board);
  Task(command, message, &board);
  Task(command, message, &board);
  Task task = Task(command, message, &board);

  if (task.get_id() != 3) {
    std::cout << "Task id test failed!\n";
    return;
  }

  Task task_clone = task;
  Task task_clone2(task);

  if (task == task_clone && task == task && task == task_clone2) {
    std::cout << "Task tests passed!\n";
  } else {
    std::cout << "Task clone test failed!\n";
  }
}

void registration_tests() {
  Backlog backlog;
  Board board;
  SocialNetwork social_network(backlog);
  User user("Test User", &social_network);

  social_network.register_user(user, &board);

  bool p = false;
  std::vector<User> users = social_network.get_users();
  for (User u : users) {
    if (u == user) {
      p = true;
      break;
    }
  }

  if (!p || !social_network.check_user_registered(user) ||
      *social_network.user_board(user) != board) {
    std::cout << "User not registered!\n";
  }
  std::cout << "Registration tests passed!\n";
}


int main() {
  user_tests();
  worker_tests();
  message_tests();
  task_tests();
  registration_tests();
}
