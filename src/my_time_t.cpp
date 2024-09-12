#include "my_time_t.h"

void my_time_t::normalize_time() {
  while (min >= 60) {
    min -= 60;
    hour++;
  }
  while (min < 0) {
    min += 60;
    hour--;
  }
}

my_time_t::my_time_t(unsigned in_hour, unsigned in_min)
    : hour(in_hour % 24), min(in_min) {
  normalize_time();
}

my_time_t my_time_t::operator=(const my_time_t& other) {
  hour = other.hour;
  min = other.min;
  return *this;
}

bool my_time_t::operator>(const my_time_t& other) {
  if (hour == other.hour) return min > other.min;
  return hour > other.hour;
}

bool my_time_t::operator<(const my_time_t& other) {
  if (hour == other.hour) return min < other.min;
  return hour < other.hour;
}

my_time_t my_time_t::operator-(const my_time_t& other) const {
  my_time_t result(hour - other.hour, min - other.min);
  return result;
}

my_time_t my_time_t::operator+(const my_time_t& other) const {
  my_time_t result(hour + other.hour, min + other.min);
  return result;
};

std::string my_time_t::get_str() {
  char buff[6];
  sprintf(buff, "%02u:%02u", hour, min);
  return std::string(buff);
}

int my_time_t::get_round_up() const {
  if (min > 0) return hour + 1;
  return hour;
}

void my_time_t::set_time(unsigned a, unsigned b) {
  hour = a % 24;
  min = b;
}

//ИСКЛЮЧЕНИЕ
void my_time_t::set_time(const std::string str) {  // [XX:XX]

  if (sscanf(str.c_str(), "%2u:%2u", &hour, &min) != 2)
    throw CompClubException("set_time(string):format error");
  hour %= 24;
  min %= 60;
}
