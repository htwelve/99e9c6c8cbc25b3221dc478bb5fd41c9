#include "CompClub.h"

void ComputerClubIO::input_processor() {
  Event event;
  while (event.attribute_one != CLOSING_TIME) {
    event = read_event();
    output_processor(event);
  }
}

void ComputerClubIO::output_processor(IEvent & event){
  event.print_event();
}

Event ComputerClubIO::parse_event_from_str(std::string input) {
  Event event_obj;
  std::istringstream sin(input);
  std::string tmp;

  try {
    std::getline(sin, tmp, ' ');

    event_obj.timestamp.set_time(input);

    std::getline(sin, tmp, ' ');

    event_obj.attribute_one = std::stoi(tmp);

    std::getline(sin, tmp, ' ');

    event_obj.client_name = tmp;

    if (event_obj.attribute_one == CLIENT_TOOK_TABLE_INPUT) {
      std::getline(sin, tmp);
      event_obj.attribute_two = std::stoi(tmp);
    }
  } catch (...) {
    std::cout << input << std::endl;
    throw CompClubException("parsing error");
  }
  return event_obj;
}

Event ComputerClubIO::read_event() {
  Event event_obj;
  std::string input;

  try
  {
    std::getline(fin, input);
  }
  catch(const std::exception& e)
  { 
    event_obj.attribute_one = CLOSING_TIME;
    return event_obj;
  }
  
  event_obj = parse_event_from_str(input);

  return event_obj;
}

ComputerClubIO::ComputerClubIO(std::string path) {
  fin.exceptions(std::ifstream::badbit | std::ifstream::failbit);
  try {
    fin.open(path);
  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
    throw CompClubException("ComputeClubIO:filename error");
  }
};

ComputerClubIO::~ComputerClubIO() {
  if (fin.is_open()) {
    fin.close();
  }
};

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
    ;
  }
  open_time.set_time(h1, m1);
  close_time.set_time(h2, m2);

  std::getline(fin, input);
  ret_flag = sscanf(input.c_str(), "%lu", &price);
  if (ret_flag != 1) {
    std::cout << input << std::endl;
    throw CompClubException("parse_initial:format error");
    ;
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