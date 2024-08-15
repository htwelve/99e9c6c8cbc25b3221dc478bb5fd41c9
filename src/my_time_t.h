#pragma once

#include <iostream>

class my_time_t {
 private:
  int hour = 0;  //[0-23]
  int min = 0;   //[0-59]

  void normalize_time();

 public:
  my_time_t(){};

  my_time_t(unsigned in_hour, unsigned in_min);

  my_time_t(const my_time_t& other) : my_time_t(other.hour, other.min) {}

  my_time_t(const std::string str);

  my_time_t operator=(const my_time_t& other);

  my_time_t operator-(const my_time_t& other) const;

  my_time_t operator+(const my_time_t& other) const;

  std::string get_str();

  int get_round_up() const;

  void set_time(unsigned a, unsigned b);
};