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

 protected:
  std::ifstream fin;

  void input_processor();

  std::string output_processor(IEvent& msg);

  ComputerClubIO(std::string path);

  ~ComputerClubIO();
};
