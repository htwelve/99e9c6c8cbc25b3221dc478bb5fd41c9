#pragma once

#include <iostream>

class CompClubException : public std::exception {
 private:
  std::string msg;

 public:
  CompClubException(std::string in_msg) : msg(in_msg) {}
  virtual const char *what() const noexcept { return msg.c_str(); }
};