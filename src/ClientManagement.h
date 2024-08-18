#pragma once

#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

#include "Table.h"
#include "events.h"
#include "my_time_t.h"

class ClientManagement {
 private:
  Event move_to_table_if_empty(my_time_t timestamp);

  bool check_open_hours(my_time_t timestamp);

  std::vector<Table>::iterator find_in_tables(std::string client_name);

  std::vector<Table>::iterator find_empty_table();

  std::vector<Table>::iterator find_non_empty_table();

  std::vector<std::string>::iterator find_in_reception(std::string name);

  bool is_client_inside(std::string name);

  bool is_table_free(size_t table_id);

 protected:
  my_time_t open_time;

  my_time_t close_time;

  size_t price;

  size_t number_of_tables;

  // std::vector<std::string>::iterator a
  std::vector<std::string> reception;
  // std::vector<Table>::iterator a
  std::vector<Table> tables;

  ClientManagement() {}

  void createTables();

  Event add_client_to_queue(Event event);

  Event add_client_to_table(Event event);

  Event client_awaits(Event event);

  Event remove_client(Event event);

  Event closing_sequence();

  void all_clients_to_queue();
};