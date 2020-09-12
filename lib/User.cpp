#include "User.h"
#include "SocialNetwork.h"

std::atomic_int User::next_user_id = 0;

User::User(){}

User::User(std::string name) {
  this->name = name;
  this->id = next_user_id.fetch_add(1);
}

User::User(std::string name, SocialNetwork *social_network) {
  this->name = name;
  this->id = next_user_id.fetch_add(1);
  this->social_network = social_network;
}

User::User(const User &user) {
  this->name = user.name;
  this->id = user.id;
}

User& User::operator=(const User &user) {
  this->name = user.name;
  this->id = user.id;
  return *this;
}

std::string User::get_name() {
  return name;
}

int User::get_id() const {
  return id;
}

int User::hash_code() const {
  return id;
}

std::ostream& operator<<(std::ostream &os, User &user) {
  return os << "User{id = " << user.id << ", name = " << user.name << "'}";
}

bool User::operator==(void *other) {
  if (this == other) {
    return true;
  }
  if (other == nullptr || typeid(this) != typeid(other)) {
    return false;
  }

  User *user= (User*) other;

  return id == user->get_id();
}

bool User::operator==(User &user) {
  if (this == &user) {
    return true;
  }

  if (user == nullptr) {
    return false;
  }

  return id == user.get_id();
}

bool User::operator<(const User &other) const {
  return this->get_id() < other.get_id();
}

void User::run(SocialNetwork *social_network) {
  srand(time(NULL));
  int i = 0;
  while(i < 5) {
    // 10% chance for the user to exit
    if (rand()% 10 == 0) {
      break;
    }
    ++i;

    std::vector<User*> users = social_network->get_users(); // TODO

    std::random_shuffle(users.begin(), users.end());
    int picks = rand() % users.size();

    std::set<User*> picked_users(users.begin(), users.begin() + picks);
    if (picked_users.count(this)) {
      picked_users.erase(this);
    }
    std::string msg = "Message";
    social_network->post_message(this, picked_users, msg);

    std::set<Message*> ms = social_network->user_board(this)->get_board_snapshot();
    std::vector<Message*> snap(ms.begin(), ms.end());
    std::vector<Message*> filtered_snap;
    for (Message* m : snap) {
      if (m->get_sender()->get_id() != this->get_id()) {
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
      if (!sent[filtered_snap[i]->hash_code()]) {
        social_network->delete_message(filtered_snap[i]); // TODO
        sent[filtered_snap[i]->hash_code()] = true;
      }
    }
  }
}

void User::start(SocialNetwork *social_network) {
  thr = std::thread(&User::run, this, social_network);
}

void User::join() {
  thr.join();
}

void User::reset_id() {
  next_user_id.store(0, std::memory_order_seq_cst);
}
