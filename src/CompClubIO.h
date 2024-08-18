#pragma once

#include <fstream>
#include <queue>
#include <sstream>

#include "events.h"

class ComputerClubIO {
 private:
  Event parse_event_from_str(std::string input);

  Event read_event();

  virtual void parse_initial_values(){};

  virtual Event update_state(Event& event) {
    return event;
  };

  virtual void print_workday_summary(){};

  virtual void print_open_summary(){};

 protected:
  std::ifstream fin;

  void IO_processor();

  std::string output_processor(Event msg);

  ComputerClubIO(std::string path);

  ~ComputerClubIO();
};
