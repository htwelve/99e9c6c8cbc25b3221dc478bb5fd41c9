#include "Table.h"

void Table::set_client(std::string &client, my_time_t timestamp) {
  table_client = client;

  occupied = true;

  client_arrival_timestamp = timestamp;
};

std::string Table::get_client_name() {
  if (occupied) return table_client;

  return std::string();
}

void Table::remove_client(my_time_t timestamp) {
  occupied = false;

  my_time_t paid_time = client_arrival_timestamp - timestamp;

  total_paid_hours += paid_time.get_round_up();

  total_time_occupied = total_time_occupied + paid_time;
}