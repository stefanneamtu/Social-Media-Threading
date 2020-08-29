#include "User.h"

std::atomic_int User::next_id = 0;

User::User(std::string name, SocialNetwork *social_network) {
  this->name = name;
  this->social_network = social_network;
  this->id = next_id.fetch_add(1);
}

User::User(const User &user) {
  this->name = user.name;
  this->social_network = user.social_network;
  this->id = user.id;
}

std::string User::get_name() {
  return name;
}

int User::get_id() {
  return id;
}

int User::hash_code() {
  return id;
}

std::ostream& operator<<(std::ostream &os, User &user) {
  return os << "User{id = " << user.id << ", name = " << user.name << "'}";
}

void User::run() {
  srand(time(NULL));
  while(true) {
    // 10% chance for the user to exit
    if (rand()% 10 == 0) {
      break;
    }

    std::vector<User> users = social_network->get_users(); // TODO

    std::random_shuffle(users.begin(), users.end());
    int picks = rand() % users.size();

    std::vector<User> picked_users(users.begin(), users.begin() + picks);
    social_network->post_message(this, picked_users, "Message");

    std::vector<Message> snap = social_network->user_board(this).get_board_snapshot(); // TODO
    std::vector<Message> filtered_snap;
    for (Message m : snap) {
      if (m.get_sender().get_id() != this->get_id()) {
        filtered_snap.push_back(m);
      }
    }
    //std::copy_if(snap.begin(), snap.end(), std::back_inserter(filtered_snap), [](Message m){return m.get_sender().get_id() != id;})
    if (filtered_snap.size() == 0) {
      continue;
    }

    std::random_shuffle(filtered_snap.begin(), filtered_snap.end());
    picks = rand() % filtered_snap.size();

    for (int i = 0; i < picks; ++i) {
      if (!sent[filtered_snap[i].hash_code()]) {
        social_network->delete_message(filtered_snap[i]); // TODO
        sent[filtered_snap[i].hash_code()] = true;
      }
    }
  }
}

void User::start() {
  thr = std::thread(&User::run, this);
}

void User::join() {
  thr.join();
}
