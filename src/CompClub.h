#pragma once

#include <array>
#include <fstream>
#include <iostream>
#include <queue>
#include <vector>

#include "my_time_t.h"

//не нужно
std::array<std::string, 5> Errors = {"NotOpenYet", "ICanWaitNoLonger",
                                     "PlaceIsBusy",
                                     "ClientUnknown"
                                     "YouShallNotPass"};

enum EventTypes {
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
  virtual void print_event(){};
};

struct Event : IEvent {

  my_time_t timestamp;

  EventTypes attribute_one = OK;

  std::string client_name;

  int second_attribute = -1;

  void print_event() override {
    std::cout << timestamp.get_str() << " " << attribute_one << " "
              << client_name;
    if (second_attribute != -1) std::cout << " " << second_attribute;
    std::cout << std::endl;
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

class Table {
 private:
  int table_id;
  Client* table_client = nullptr;
  my_time_t client_arrival_timestamp;
  int total_money_collected = 0;

 public:
  Table(int input_table_id) : table_id(input_table_id){};
  int get_profit() {return total_money_collected;};
};

class Client {
 private:
  std::string name;
 public:
  Client(std::string input_name) : name(input_name){};
};


//написать отдельный интерфейс для клуба
class ComputerClub {
 private:
  std::ifstream fin;

  my_time_t open_time;
  my_time_t close_time;

  size_t number_of_tables;
  size_t price;

  std::queue<Client> reception_queue;  // reserve number_of_tables

  std::vector<Table> tables;  // reserve number_of_tables

  void parse_initial_values();

 public:
  ComputerClub(std::string path);
  ~ComputerClub();



//СЫРОЕ
  std::vector<IEvent> update_state(IEvent Event){
    std::vector<IEvent> vec;
    ErrorEvent err("error");
    vec.emplace_back(err);
    return vec;
  };

  void initialize();

  //отладка
  void print_info();
};

// class ComputerClubIO  {
//   private:
//   ComputerClubIO(){};
//   public:
//   static Event read_event(){};

// };