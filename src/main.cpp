#include "CompClub.h"

int main(int argc, char const *argv[]) {
  ComputerClub club{std::string(argv[1])};

  club.initialize();
  club.print_info();
  return 0;
}
