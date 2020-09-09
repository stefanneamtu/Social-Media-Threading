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
  Backlog backlog;
  Board boards[100];
  SocialNetwork social_network(&backlog);

  const int workers_no = 40;
  std::vector<Worker*> workers;
  std::cout << 1 << std::endl;
  for (int i = 0; i < workers_no; ++i) {
    workers.push_back(new Worker(&backlog));
    workers[i]->start();
  }
  std::cout << 2 << std::endl;

  const int users_no = 100;
  std::vector<User*> users;
  for (int i = 0; i < users_no; ++i) {
    users.push_back(new User("Simulation"));
    social_network.register_user(users[i], boards + i);
    users[i]->start(&social_network);
  }
  std::cout << 3 << std::endl;

  for (User* user : users) {
    user->join();
  }

  for (Worker* worker : workers) {
    worker->interrupt();
  }

  for (Worker* worker : workers) {
    worker->join();
  }
  std::cout << 4 << std::endl;

  return 0;
}
