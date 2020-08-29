#ifndef SOCIALMEDIATHREADING_MESSAGE_H
#define SOCIALMEDIATHREADING_MESSAGE_H

#include <atomic>
#include <vector>
#include <string>
#include <iostream>
#include <set>

#include "User.h"

class Message {

  private:
    static std::atomic_int next_id;
    User sender;
    std::set<User> recipients;
    std::string text;
    int id;

  public:
    Message();
    Message(User sender, std::set<User> recipients, std::string text);
    User get_sender();
    std::set<User> get_recipients();
    std :: string get_text();
    int get_id();
    int hash_code();
    std :: ostream& operator<<(std::ostream &strm);
    bool operator==(void *other);
};

#endif //SOCIALMEDIATHREADING_MESSAGE_H
