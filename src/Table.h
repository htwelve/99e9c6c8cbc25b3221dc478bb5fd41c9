#pragma once

#include <iostream>

#include "my_time_t.h"

class Table {
 private:
  int table_id;

  bool occupied = false;

  std::string table_client;

  my_time_t client_arrival_timestamp;

  my_time_t total_time_occupied = my_time_t(0, 0);

  int total_paid_hours = 0;

 public:
  Table(int input_table_id) : table_id(input_table_id){};

  int get_paid_hours() { return total_paid_hours; };

  int get_id() { return table_id; };

  my_time_t get_total_time() { return total_time_occupied; };

  void set_client(std::string &client, my_time_t timestamp);

  std::string get_client_name();

  bool is_occupied() { return occupied; };

  void remove_client(my_time_t timestamp);
};