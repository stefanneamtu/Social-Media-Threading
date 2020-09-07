#ifndef SOCIALMEDIATHREADING_USER_H
#define SOCIALMEDIATHREADING_USER_H

#include <iostream>
#include <thread>
#include <pthread.h>
#include <atomic>
#include <vector>
#include <algorithm>
#include <bitset>

class Backlog;
class SocialNetwork;

class User {
  private:
    static std::atomic_int next_user_id;
    std::thread thr;
    int id;
    std::string name;
    std::bitset<10000> sent;
    SocialNetwork *social_network;

  public:
    User();
    User(std::string name);
    User(std::string name, SocialNetwork *social_network);
    User(const User &user);
    User& operator=(const User &user);
    std::string get_name();
    int get_id() const;
    int hash_code() const;
    friend std::ostream& operator<<(std::ostream& os, User& user);
    bool operator==(void *other);
    bool operator==(User &other);
    bool operator<(const User &other) const;
    void run(SocialNetwork *social_network);
    void start(SocialNetwork *social_network);
    void join();
    static void reset_id(); // for testing purposes
};


#endif //SOCIALMEDIATHREADING_USER_H
