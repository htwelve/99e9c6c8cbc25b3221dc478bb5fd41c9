#include "CompClub.h"

ComputerClub::ComputerClub(std::string path) : ComputerClubIO(path) {
  initialize();
}

void ComputerClub::parse_initial_values() {
  std::string input;

  int ret_flag = 0;

  std::getline(fin, input);

  ret_flag = sscanf(input.c_str(), "%lu", &number_of_tables);

  if (ret_flag != 1) {
    std::cout << input << std::endl;

    throw CompClubException("parse_initial:format error");
  }

  int h1, m1, h2, m2;

  std::getline(fin, input);

  ret_flag = sscanf(input.c_str(), "%2u:%2u %2u:%2u", &h1, &m1, &h2, &m2);

  if (ret_flag != 4) {
    std::cout << input << std::endl;

    throw CompClubException("parse_initial:format error");
  }

  open_time.set_time(h1, m1);

  close_time.set_time(h2, m2);

  std::getline(fin, input);

  ret_flag = sscanf(input.c_str(), "%lu", &price);

  if (ret_flag != 1) {
    std::cout << input << std::endl;

    throw CompClubException("parse_initial:format error");
  }
}

void ComputerClub::print_info() {
  std::cout << "Open time: " << open_time.get_str() << std::endl;
  std::cout << "Price: " << price << std::endl;
  std::cout << "Tables: " << number_of_tables << std::endl;
  std::cout << "Close time: " << close_time.get_str() << std::endl;
  std::cout << "Sum time: " << (close_time = close_time + open_time).get_str()
            << std::endl;
}

void ComputerClub::initialize() { parse_initial_values(); }

IEvent &ComputerClub::update_state(Event & in_event) {
  switch (in_event.attribute_one)
  {

  case CLIENT_ARRIVED_INPUT:
    
    return add_client_to_queue(in_event);

  case CLIENT_TOOK_TABLE_INPUT:
    
    return add_client_to_table(in_event);

  case CLIENT_AWAITS_INPUT:

    return client_awaits(in_event);

  case CLIENT_LEFT_INPUT:

    return remove_client(in_event);

  case CLOSING_TIME:

    all_clients_to_queue();
    
    return closing_sequence();

  default:
    IEvent tmp(in_event.timestamp, OK);
    return tmp;
  }
}