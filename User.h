#ifndef SOCIALMEDIATHREADING_USER_H
#define SOCIALMEDIATHREADING_USER_H

#include <iostream>
#include <thread>
#include <atomic>
#include <vector>
#include <algorithm>
#include <bitset>

#include "SocialNetwork.h"
class Message;

class User {
  private:
    static std::atomic_int next_id;
    std::thread thr;
    SocialNetwork *social_network;
    int id;
    std::string name;
    std::bitset<10000> sent;

  public:
    User(std::string name, SocialNetwork *social_network);
    User(const User &user);
    std::string get_name();
    int get_id();
    int hash_code();
    friend std::ostream& operator<<(std::ostream& os, User& user);
    void run();
    void start();
    void join();
};

#endif //SOCIALMEDIATHREADING_USER_H
