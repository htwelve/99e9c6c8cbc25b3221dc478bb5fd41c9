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
  std::getline(fin, input);
  ret_flag = sscanf(input.c_str(), "%lu", &number_of_tables);
  if (ret_flag != 1) {
    std::cout << input << std::endl;
    throw;
  }


  int h1,m1,h2,m2;
  std::getline(fin, input);
  ret_flag = sscanf(input.c_str(), "%2u:%2u %2u:%2u", &h1,
                    &m1, &h2,
                    &m2);
  if (ret_flag != 4) {
    std::cout << input << std::endl;
    throw;
  }
  open_time.set_time(h1,m1);
  close_time.set_time(h2,m2);


  std::getline(fin, input);
  ret_flag = sscanf(input.c_str(), "%lu", &price);
  if (ret_flag != 1) {
    std::cout << input << std::endl;
    throw;
  }
}

void ComputerClub::print_info() {
  
  std::cout << "Open time: " << open_time.get_str() << std::endl;
  std::cout << "Price: " << price << std::endl;
  std::cout << "Tables: " << number_of_tables << std::endl;
  std::cout << "Close time: " << close_time.get_str() << std::endl;
  std::cout << "Sum time: " << (close_time = close_time + open_time).get_str() << std::endl;
}

void ComputerClub::initialize() { parse_initial_values(); }