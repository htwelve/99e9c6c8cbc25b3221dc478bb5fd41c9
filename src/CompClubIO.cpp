#include "CompClubIO.h"

void ComputerClubIO::input_processor() {
  Event event;
  while (event.attribute_one != CLOSING_TIME) {
    event = read_event();
    std::cout << output_processor(event);
  }
}

std::string ComputerClubIO::output_processor(IEvent& event) {
  return event.get_str();
}

Event ComputerClubIO::parse_event_from_str(std::string input) {
  Event event_obj;
  std::istringstream sin(input);
  std::string tmp;

  try {
    std::getline(sin, tmp, ' ');

    event_obj.timestamp.set_time(input);

    std::getline(sin, tmp, ' ');

    event_obj.attribute_one = std::stoi(tmp);

    std::getline(sin, tmp, ' ');

    event_obj.client_name = tmp;

    if (event_obj.attribute_one == CLIENT_TOOK_TABLE_INPUT) {
      std::getline(sin, tmp);
      event_obj.attribute_two = std::stoi(tmp);
    }
  } catch (...) {
    std::cout << input << std::endl;
    throw CompClubException("parsing error");
  }
  return event_obj;
}

Event ComputerClubIO::read_event() {
  Event event_obj;
  std::string input;

  try {
    std::getline(fin, input);
  } catch (const std::exception& e) {
    event_obj.attribute_one = CLOSING_TIME;
    return event_obj;
  }

  event_obj = parse_event_from_str(input);

  return event_obj;
}

ComputerClubIO::ComputerClubIO(std::string path) {
  fin.exceptions(std::ifstream::badbit | std::ifstream::failbit);
  try {
    fin.open(path);
  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
    throw CompClubException("ComputeClubIO:filename error");
  }
};

ComputerClubIO::~ComputerClubIO() {
  if (fin.is_open()) {
    fin.close();
  }
};
