#pragma once

#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>
#include <vector>

#include "CompClubException.h"
#include "events.h"
#include "my_time_t.h"

class Client {
 private:
  std::string name;

 public:
  Client(std::string input_name) : name(input_name){};
};

class Table {
 private:
  int table_id;

  Client* table_client = nullptr;

  my_time_t client_arrival_timestamp;

  my_time_t total_time_occupied = my_time_t(0, 0);

  int total_money_collected = 0;

 public:
  Table(int input_table_id) : table_id(input_table_id){};

  int get_profit() { return total_money_collected; };

  my_time_t get_total_time() { return total_time_occupied; };

  void set_client();
};

class ComputerClubIO {
 private:
  Event parse_event_from_str(std::string input);

  Event read_event();

  virtual void parse_initial_values(){};

 protected:
  std::ifstream fin;

  void input_processor();

  void output_processor(IEvent & event);

  ComputerClubIO(std::string path);

  ~ComputerClubIO();
};

class ComputerClub : public ComputerClubIO {
 private:
  my_time_t open_time;
  my_time_t close_time;

  size_t number_of_tables;
  size_t price;

  // "очередь" выгоднее сделать вектором
  std::vector<Client> reception_queue;

  std::vector<Table> tables;

  void parse_initial_values() override;

  void initialize();

 public:
  //может бросать исключения
  ComputerClub(std::string path) : ComputerClubIO(path) {
    initialize();
    tables.reserve(number_of_tables);
    reception_queue.reserve(number_of_tables);

    //подразумеваем что количество столов небольшое поэтому инициализируем сразу
    //все
    for (size_t i = 1; i <= number_of_tables; i++) {
      tables.emplace_back(Table(i));
    }
  };

  ~ComputerClub(){};

  void start() { input_processor(); };

  //СЫРОЕ
  std::vector<IEvent> update_state(IEvent Event) {
    std::vector<IEvent> vec;
    ErrorEvent err("error");
    vec.emplace_back(err);
    return vec;
  };

  //отладка
  void print_info();
};
