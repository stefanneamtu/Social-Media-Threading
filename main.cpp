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
  for (int i = 0; i < workers_no; ++i) {
    workers.push_back(new Worker(backlog));
  }

  const int users_no = 100;
  std::vector<User*> users;
  for (int i = 0; i < users_no; ++i) {
    users.push_back(new User("Simulation"));
    social_network->register_user(users[i], boards + i);
    users[i]->start(social_network);
  }

  for (int i = 0; i < workers_no; ++i) {
    workers[i]->start();
  }

  std::this_thread::sleep_for(std::chrono::milliseconds(1000));

  for (User* user : users) {
    user->join();
  }

  for (Worker* worker : workers) {
    worker->interrupt();
  }

  for (Worker* worker : workers) {
    worker->join();
  }

  for (int i = 0; i < users_no; ++i) {
    std::cout << boards[i].size() << "\n";
  }

  for (User* user : users) {
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
