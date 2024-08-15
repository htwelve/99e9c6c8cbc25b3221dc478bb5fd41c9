
#include <array>
#include <ctime>
#include <fstream>
#include <iostream>
#include <queue>

// std::array<std::string, 5> Errors = {"NotOpenYet", "ICanWaitNoLonger",
//                                      "PlaceIsBusy",
//                                      "ClientUnknown"
//                                      "YouShallNotPass"};

// enum InputEvents {
//   CLIENT_ARRIVED = 1,
//   CLIENT_TOOK_TABLE = 2,
//   CLIENT_AWAITS = 3,
//   CLIENT_LEFT = 4,
// };

// enum OutputEvents {
//   CLIENT_LEFT = 11,
//   CLIENT_TOOK_TABLE = 12,
//   ERROR = 13,
// };

class Table {
 private:
  int table_id;
  bool occupied = 0;

 public:
  Table(int input_table_id) : table_id(input_table_id){};
};

class Client {
 private:
  std::string name;

 public:
  Client(std::string input_name) : name(input_name){};
};

class my_time_t
{
private:
  int hour = 0; //[0-23]
  int min = 0;  //[0-59]

  void normalize_time() {
    while(min >= 60){
      min -= 60;
      hour++;
    }
    while(min < 0){
      min += 60;
      hour--;
    }    
  };
public:
  my_time_t(){};
  my_time_t(unsigned in_hour, unsigned in_min) : hour(in_hour % 24), min(in_min) {
    normalize_time();
  };

  my_time_t(const my_time_t & other): my_time_t(other.hour,other.min){
  }

  my_time_t(const std::string str){ // [XX:XX]

    sscanf(str.c_str(), "%2u:%2u", &hour,&min);
    hour %= 24;
    min %= 60;
  }

  my_time_t operator=(const my_time_t & other) { 
    hour = other.hour;
    min = other.min;
    return *this;
  };

  my_time_t operator-(const my_time_t & other) const { 
    my_time_t result(hour - other.hour, min - other.min);
    return result;
  };

    my_time_t operator+ (const my_time_t & other) const { 
    my_time_t result(hour + other.hour, min + other.min);
    return result;
  };

  std::string get_str(){
    char buff[6];
    sprintf(buff,"%02u:%02u", hour, min);
    return std::string(buff);
  }

  int get_round_up(){
    if(min > 0) return ++hour; 
    return hour;
  };

  void set_time(unsigned a, unsigned b){
    hour = a % 24;
    min = b;
  }
};




class ComputerClub {
 private:
  std::ifstream fin;

  my_time_t open_time;
  my_time_t close_time;

  size_t number_of_tables;
  size_t price;

  std::queue<Client> reception_queue;

  std::vector<Table> tables;

  void parse_initial_values();

 public:
  
  ComputerClub(std::string path);
  ~ComputerClub();

  void initialize();
  void print_info();
};
