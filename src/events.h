#pragma once

#include <array>
#include <iostream>

#include "my_time_t.h"

// std::array<std::string, 5> Errors = {"NotOpenYet", "ICanWaitNoLonger",
//                                      "PlaceIsBusy",
//                                      "ClientUnknown"
//                                      "YouShallNotPass"};



enum EventTypes {
  CLOSING_TIME = -1,
  OK = 0,
  CLIENT_ARRIVED_INPUT = 1,
  CLIENT_TOOK_TABLE_INPUT = 2,
  CLIENT_AWAITS_INPUT = 3,
  CLIENT_LEFT_INPUT = 4,

  CLIENT_LEFT_OUTPUT = 11,
  CLIENT_TOOK_TABLE_OUTPUT = 12,
  ERROR_OUTPUT = 13,
};

struct IEvent {
  virtual void print_event(){
  };
};

struct Event : IEvent {
  my_time_t timestamp;

  int attribute_one = OK;

  std::string client_name;

  int attribute_two = -1;

  void print_event() override {
    if(attribute_one != CLOSING_TIME){
    std::cout << timestamp.get_str() << " ";
    std::cout <<(int) attribute_one << " " << client_name;
    if (attribute_two != -1) std::cout << " " << attribute_two;
    std::cout << std::endl;
    }
  };
};

struct ErrorEvent : IEvent {
  my_time_t timestamp;

  std::string err_msg;

  ErrorEvent(std::string in_err_msg) : err_msg(in_err_msg){};

  void print_event() override {
    std::cout << timestamp.get_str() << " 13 " << err_msg << std::endl;
  };
};
