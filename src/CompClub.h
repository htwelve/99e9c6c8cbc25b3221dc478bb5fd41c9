#pragma once

#include <iostream>

#include "ClientManagement.h"
#include "CompClubException.h"
#include "CompClubIO.h"
#include "events.h"
#include "my_time_t.h"

class ComputerClub : public ClientManagement, public ComputerClubIO {
 private:
  void parse_initial_values() override;

  void initialize();

  IEvent& update_state(IEvent event);

 public:
  //может бросать исключения
  ComputerClub(std::string path);

  ~ComputerClub(){};

  void start() {
    createTables();
    input_processor();
  };

  //отладка
  void print_info();
};
