#include "Message.h"

std::atomic_int Message::next_message_id = 0;

Message::Message(){}

Message::Message(User* sender, std::set<User*> recipients, std::string text) {
  this->sender = sender;
  this->recipients = recipients;
  this->text = text;
  this->id = next_message_id++;
}

User* Message::get_sender() {
  return sender;
}

std::set<User*> Message::get_recipients() {
  return recipients;
}

std::string Message::get_text() {
  return text;
}

int Message::get_id() const {
  return id;
}

int Message::hash_code() const {
  return id;
}

std::ostream& Message::operator<<(std::ostream &strm) {
  strm << "Message{sender = " << sender << ", recipients = ";
  for (User* recipient : recipients) {
    strm << *recipient << ", ";
  }
  strm << ", text='" << text << "', id = " << id << "}";
  return strm;
}

bool Message::operator==(void *other) {
  if (this == other) {
    return true;
  }
  if (other == nullptr || typeid(this) == typeid(other)) {
    return false;
  }

  Message *message = (Message*) other;

  return id == message->get_id();
}

bool Message::operator==(Message other) {
  if (this == &other) {
    return true;
  }

  return id == other.get_id();
}

const bool Message::operator<(const Message &other) const {
  return this->id < other.get_id();
}


