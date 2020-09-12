#include <iostream>
#include <vector>
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

int main() {
  Backlog* backlog = new Backlog();
  Board boards[100];
  SocialNetwork* social_network = new SocialNetwork(backlog);

  const int workers_no = 40;
  std::vector<Worker*> workers;
  std::cout << 1 << std::endl;
  for (int i = 0; i < workers_no; ++i) {
    workers.push_back(new Worker(backlog));
    workers[i]->start();
  }
  std::cout << 2 << std::endl;

  const int users_no = 10;
  std::vector<User*> users;
  for (int i = 0; i < users_no; ++i) {
    users.push_back(new User("Simulation"));
    social_network->register_user(users[i], boards + i);
    users[i]->start(social_network);
  }
  std::cout << 3 << std::endl;

  for (User* user : users) {
    user->join();
  }
  std::cout << 4 << std::endl;

  for (Worker* worker : workers) {
    worker->interrupt();
  }
  std::cout << 5 << std::endl;

  for (Worker* worker : workers) {
    worker->join();
  }
  std::cout << 6 << std::endl;

  for (User* user : users) {
    social_network->user_board(user)->clear_board();
    delete(user);
  }

  for (Worker* worker : workers) {
    delete(worker);
  }

  backlog->clear_backlog();
  delete(backlog);
  delete(social_network);

  return 0;
}
