#include "CompClub.h"

int main(int argc, char const *argv[]) {
  if (argc >= 2) {
    ComputerClub club{std::string(argv[1])};
    club.start();
  } else {
    std::cout << "Usage: ./test <dataset>" << std::endl;
  }
  return 0;
}
