#pragma once

#include <array>
#include <iostream>
#include <sstream>

#include "my_time_t.h"

enum EventTypes {
  CLOSING_TIME = -1,
  CLIENT_ARRIVED_INPUT = 1,
  CLIENT_TOOK_TABLE_INPUT = 2,
  CLIENT_AWAITS_INPUT = 3,
  CLIENT_LEFT_INPUT = 4,

  OK = 0,
  CLIENT_LEFT_OUTPUT = 11,
  CLIENT_TOOK_TABLE_OUTPUT = 12,
  ERROR_OUTPUT = 13,
};

struct IEvent {
  my_time_t timestamp;
  int attribute_one = OK;

  IEvent(){};

  IEvent(my_time_t input_timestamp, int attr)
      : timestamp(timestamp), attribute_one(attr){};

  virtual std::string get_str(){
      // std::ostringstream sout;
      // sout << timestamp.get_str() << " " << attribute_one << std::endl;
      // return sout.str();
  };
};

struct Event : IEvent {
  std::string client_name;

  int attribute_two = -1;

  Event(){};

  Event(std::string input_name, my_time_t input_timestamp, int attr1,
        int attr2 = -1)
      : IEvent(input_timestamp, attr1),
        client_name(input_name),
        attribute_two(attr2) {}

  std::string get_str() override {
    std::ostringstream sout;
    if (attribute_one != CLOSING_TIME && attribute_one != OK) {
      sout << timestamp.get_str() << " ";
      sout << attribute_one << " " << client_name;
      if (attribute_two != -1) sout << " " << attribute_two;
      sout << std::endl;
    }
    return sout.str();
  };
};

struct ErrorEvent : IEvent {
  std::string err_msg;

  ErrorEvent(){};

  ErrorEvent(std::string in_err_msg, my_time_t input_timestamp)
      : IEvent(input_timestamp, 13), err_msg(in_err_msg){};

  std::string get_str() override {
    std::ostringstream sout;
    sout << timestamp.get_str() << " 13 " << err_msg << std::endl;
    return sout.str();
  };
};
