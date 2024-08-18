#include "ClientManagement.h"

bool ClientManagement::check_open_hours(my_time_t timestamp) {
  if (timestamp < close_time && timestamp > open_time) return true;
  return false;
}

bool ClientManagement::is_client_inside(std::string name) {
  if (find_in_reception(name) == reception.end() &&
      find_in_tables(name) == tables.end()) {
    return false;
  }
  return true;
}

bool ClientManagement::is_table_free(size_t table_id) {
  table_id--;
  if (table_id < 0 || table_id > number_of_tables) return false;
  return !tables.at(table_id).is_occupied();
}

void ClientManagement::createTables() {
  //  tables.reserve(number_of_tables);

  //  reception.reserve(number_of_tables);

  for (size_t i = 1; i <= number_of_tables; i++) {
    tables.emplace_back(Table(i));
  }
}

std::vector<Table>::iterator ClientManagement::find_in_tables(
    std::string client_name) {
  auto f = [&client_name](Table table) -> bool {
    return table.get_client_name() == client_name;
  };
  return std::find_if(tables.begin(), tables.end(), f);
}

std::vector<Table>::iterator ClientManagement::find_empty_table() {
  auto f = [](Table table) -> bool { return !table.is_occupied(); };

  return std::find_if(tables.begin(), tables.end(), f);
}

std::vector<Table>::iterator ClientManagement::find_non_empty_table() {
  auto f = [](Table table) -> bool { return table.is_occupied(); };

  return std::find_if(tables.begin(), tables.end(), f);
}

std::vector<std::string>::iterator ClientManagement::find_in_reception(
    std::string name) {
  return std::find(reception.begin(), reception.end(), name);
}

Event ClientManagement::add_client_to_queue(Event event) {
  if (!check_open_hours(event.timestamp)) {
    return Event("NotOpenYet", event.timestamp, ERROR_OUTPUT);

  } else if (is_client_inside(event.client_name)) {
    return Event("YouShallNotPass", event.timestamp, ERROR_OUTPUT);

  } else {
    reception.emplace_back(event.client_name);
  }
  Event tmp("", event.timestamp, OK);
  return tmp;
};

Event ClientManagement::add_client_to_table(Event event) {
  if (!is_client_inside(event.client_name)) {
    return Event("ClientUnknown", event.timestamp, ERROR_OUTPUT);

  } else if (!is_table_free(event.attribute_two)) {
    return Event("PlaceIsBusy", event.timestamp, ERROR_OUTPUT);

  } else {
    tables.at(--event.attribute_two)
        .set_client(event.client_name, event.timestamp);

    reception.erase(find_in_reception(event.client_name));
  }

  Event tmp("", event.timestamp, OK);

  return tmp;
}

Event ClientManagement::client_awaits(Event event) {
  if (!is_client_inside(event.client_name)) {
    return Event("ClientUnknown", event.timestamp, ERROR_OUTPUT);

  } else if (find_empty_table() != tables.end()) {
    return Event("ICanWaitNoLonger", event.timestamp, ERROR_OUTPUT);

  } else if (reception.size() > number_of_tables) {
    remove_client(event);

    Event tmp(event.client_name, event.timestamp, CLIENT_LEFT_OUTPUT);

    return tmp;
  }

  Event tmp("", event.timestamp, OK);

  return tmp;
}

Event ClientManagement::remove_client(Event event) {
  auto a = find_in_tables(event.client_name);

  auto b = find_in_reception(event.client_name);

  if (a != tables.end()) {
    a.base()->remove_client(event.timestamp);

    Event tmp = move_to_table_if_empty(event.timestamp);

    return tmp;

  } else if (b != reception.end()) {
    b.base()->erase();

  } else {
    return Event("ClientUnknown", event.timestamp, ERROR_OUTPUT);
  }
  Event tmp("", event.timestamp, OK);
  return tmp;
}

Event ClientManagement::move_to_table_if_empty(my_time_t timestamp) {
  auto a = find_empty_table();
  if (!reception.empty() && a != tables.end()) {
    Event move_event(reception.front(), timestamp, CLIENT_TOOK_TABLE_OUTPUT,
                     a.base()->get_id());
    add_client_to_table(move_event);
    return move_event;
  }
  Event tmp("", timestamp, OK);
  return tmp;
};

void ClientManagement::all_clients_to_queue() {
  auto a = find_non_empty_table();
  while (a != tables.end()) {
    reception.emplace_back(a.base()->get_client_name());
    a.base()->remove_client(close_time);
    a = find_non_empty_table();
  }
  std::sort(reception.begin(), reception.end());
}

Event ClientManagement::closing_sequence() {
  if (!reception.empty()) {
    Event tmp(reception.front(), close_time, CLIENT_LEFT_OUTPUT);
    reception.erase(reception.begin());
    return tmp;
  }
  Event tmp("", close_time, OK);
  return tmp;
}