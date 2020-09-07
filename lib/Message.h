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
    static std::atomic_int next_message_id;
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
    int get_id() const;
    int hash_code() const;
    std :: ostream& operator<<(std::ostream &strm);
    bool operator==(void *other);
    bool operator==(Message other);
    const bool operator<(const Message &other) const;
};

#endif //SOCIALMEDIATHREADING_MESSAGE_H
