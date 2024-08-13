
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

class ComputerClub {
 private:
  std::ifstream fin;

  time_t open_time = time(NULL); //переделать
  time_t close_time = time(NULL);

  size_t number_of_tables;
  size_t price;

  std::queue<Client> reception_queue;

  std::vector<Table> tables;

  void parse_initial_values();

 public:
  // can call exit()
  ComputerClub(std::string path);
  ~ComputerClub();

  void initialize();
  void print_info();
};
