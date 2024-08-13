#include "CompClub.h"

ComputerClub::ComputerClub(std::string path) {
  fin.exceptions(std::ifstream::badbit | std::ifstream::failbit);
  try {
    fin.open(path);
  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
    throw; 
  }
}

ComputerClub::~ComputerClub() {
  if (fin.is_open()) {
    fin.close();
  }
}

void ComputerClub::parse_initial_values() {
  std::string input;
  int ret_flag = 0;

  tm open_time_st = *localtime(&open_time), close_time_st = *localtime(&close_time);

  std::getline(fin, input);
  ret_flag = sscanf(input.c_str(), "%lu", &number_of_tables);
  if (ret_flag != 1) {
    std::cout << input << std::endl;
    throw;
  }
  std::getline(fin, input);
  ret_flag = sscanf(input.c_str(), "%2u:%2u %2u:%2u", &open_time_st.tm_hour,
                    &open_time_st.tm_min, &close_time_st.tm_hour,
                    &close_time_st.tm_min);
  if (ret_flag != 4) {
    std::cout << input << std::endl;
    throw;
  }

  open_time = mktime(&open_time_st);
  close_time = mktime(&close_time_st);

  std::getline(fin, input);
  ret_flag = sscanf(input.c_str(), "%lu", &price);
  if (ret_flag != 1) {
    std::cout << input << std::endl;
    throw;
  }
}

void ComputerClub::print_info() {

  tm open_time_st = *localtime(&open_time), close_time_st = *localtime(&close_time);
  char tmp[6];
  strftime(tmp, 6, "%R", &open_time_st);
  std::cout << "Open time: " << tmp << std::endl;
  std::cout << "Price: " << price << std::endl;
  std::cout << "Tables: " << number_of_tables << std::endl;
  strftime(tmp, 6, "%R", &close_time_st);
  std::cout << "Close time: " << tmp << std::endl;
}

void ComputerClub::initialize() { parse_initial_values(); }