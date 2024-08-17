#include "CompClub.h"

int main(int argc, char const *argv[]) {
  ComputerClub club{std::string(argv[1])};
  // club.print_info();
  club.start();
  return 0;
}
