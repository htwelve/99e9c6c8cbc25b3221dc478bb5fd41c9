#pragma once

#include <iostream>

#include "ClientManagement.h"
#include "CompClubException.h"
#include "CompClubIO.h"
#include "events.h"
#include "my_time_t.h"

class ComputerClub final : public ClientManagement, public ComputerClubIO {
 private:
  void parse_initial_values() override;

  void initialize();

  Event update_state(Event& event) override;

  void print_workday_summary() override;

  void print_open_summary() override;

 public:
  ComputerClub(std::string path);

  ~ComputerClub(){};

  void start() {
    createTables();
    IO_processor();
  };
};
