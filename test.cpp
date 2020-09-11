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

void registration_tests() {
  Backlog backlog;
  Board board;
  SocialNetwork social_network(&backlog);
  User user("Test User", &social_network);
  User user2("Unregistered User", &social_network);

  social_network.register_user(&user, &board);

  bool p = false;
  std::vector<User*> users = social_network.get_users();
  for (User* u : users) {
    if (*u == user) {
      p = true;
      break;
    }
  }

  if (!p || !social_network.check_user_registered(&user) ||
      *social_network.user_board(&user) != board || 
      social_network.check_user_registered(&user2)) {
    std::cout << "User registration bug!\n";
    return;
  }
  std::cout << "Registration tests passed!\n";
}

void message_tests() {
  User sender = User("Sender");
  std::set<User*> recipients;
  for (int i = 0; i < 5; ++i) {
    recipients.insert(new User("Recipient"));
  }

  Message(&sender, recipients, "Message0");
  Message(&sender, recipients, "Message1");
  Message(&sender, recipients, "Message2");
  Message(&sender, recipients, "Message3");

  Message message = Message(&sender, recipients, "Message4");

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
  Task(command, &message, &board);
  Task(command, &message, &board);
  Task(command, &message, &board);
  Task task = Task(command, &message, &board);

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

void message_lifecycle_tests() {
  User::reset_id();

  Backlog backlog;
  Board board1;
  Board board2;
  Board board3;
  SocialNetwork social_network(&backlog);

  User user1("Test1", &social_network);
  User user2("Test2", &social_network);
  User user3("Test3", &social_network);

  social_network.register_user(&user1, &board1);
  social_network.register_user(&user2, &board2);
  social_network.register_user(&user3, &board3);

  // add message test
  std::set<User*> recipients;
  recipients.insert(&user2);
  recipients.insert(&user3);
  Message* sent = social_network.post_message(&user1, recipients, "Message 1");

  if (backlog.number_of_tasks_left() != 3) {
    std::cout << "Incorrect number of tasks in the backlog!\n";
    return;
  }

  std::optional<Task*> ot1 = backlog.get_next_task();
  std::optional<Task*> ot2 = backlog.get_next_task();
  std::optional<Task*> ot3 = backlog.get_next_task();

  if (backlog.number_of_tasks_left() != 0 ||
      !ot1.has_value() || !ot2.has_value() || !ot3.has_value()) {
    std::cout << "Bad task retrieval!\n";
    return;
  }

  Task* t1 = ot1.value();
  Task* t2 = ot2.value();
  Task* t3 = ot3.value();

  std::set<Board*> target_boards;
  target_boards.insert(&board1);
  target_boards.insert(&board2);
  target_boards.insert(&board3);

  if (t1->get_message()->get_id() != sent->get_id() || t1->get_command() != POST) {
    std::cout << "Task registration failure!\n";
    return;
  }
  target_boards.erase(&board1);
  if (target_boards.size() != 2) {
    std::cout << "Set size failure!\n";
    return;
  }
  
  if (t2->get_message()->get_id() != sent->get_id() || t2->get_command() != POST) {
    std::cout << "Task registration failure!\n";
    return;
  }
  target_boards.erase(&board2);
  if (target_boards.size() != 1) {
    std::cout << "Set size failure!\n";
    return;
  }

  if (t3->get_message()->get_id() != sent->get_id() || t3->get_command() != POST) {
    std::cout << "Task registration failure!\n";
    return;
  }
  target_boards.erase(&board3);
  if (target_boards.size() != 0) {
    std::cout << "Set size failure!\n";
    return;
  }

  Worker worker(&backlog);

  worker.process(t1);
  worker.process(t2);
  worker.process(t3);

  if (board1.get_board_snapshot().count(sent) != 1 || 
      board2.get_board_snapshot().count(sent) != 1 || 
      board3.get_board_snapshot().count(sent) != 1) {
    std::cout << "Messages were not added to the board!\n";
    return;
  }

  // message deletion test 
  social_network.delete_message(sent);

  if (backlog.number_of_tasks_left() != 3) {
    std::cout << "Incorrect number of tasks in the backlog!\n";
    return;
  }

  ot2 = backlog.get_next_task();
  ot3 = backlog.get_next_task();
  ot1 = backlog.get_next_task();

  if (backlog.number_of_tasks_left() != 0 ||
      !ot1.has_value() || !ot2.has_value() || !ot3.has_value()) {
    std::cout << "Bad task retrieval!\n";
    return;
  }

  t1 = ot1.value();
  t2 = ot2.value();
  t3 = ot3.value();

  target_boards.insert(&board1);
  target_boards.insert(&board2);
  target_boards.insert(&board3);

  if (t1->get_message()->get_id() != sent->get_id() || t1->get_command() != DELETE) {
    std::cout << "Task registration failure!\n";
    return;
  }
  target_boards.erase(&board1);
  if (target_boards.size() != 2) {
    std::cout << "Set size failure!\n";
    return;
  }
  
  if (t2->get_message()->get_id() != sent->get_id() || t2->get_command() != DELETE) {
    std::cout << "Task registration failure!\n";
    return;
  }
  target_boards.erase(&board2);
  if (target_boards.size() != 1) {
    std::cout << "Set size failure!\n";
    return;
  }

  if (t3->get_message()->get_id() != sent->get_id() || t3->get_command() != DELETE) {
    std::cout << "Task registration failure!\n";
    return;
  }
  target_boards.erase(&board3);
  if (target_boards.size() != 0) {
    std::cout << "Set size failure!\n";
    return;
  }

  worker.process(t1);
  worker.process(t2);
  worker.process(t3);

  if (board1.get_board_snapshot().size() != 0 || 
      board2.get_board_snapshot().size() != 0 || 
      board3.get_board_snapshot().size() != 0) {
    std::cout << "Messages were not removed to the board!\n";
    return;
  }

  std::cout << "Message lifecycle tests passed!\n";
}

int main() {
  user_tests();
  message_tests();
  task_tests();
  registration_tests();
  message_lifecycle_tests();
}
