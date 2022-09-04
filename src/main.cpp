#include <iostream>
#include <fmt/format.h>
#include <random>
#include <stdio.h>

int roll_dice() {
  static std::random_device rdev;
  static std::default_random_engine reng{rdev()};
  static std::uniform_int_distribution<int> random_dice(1, 7);
  return random_dice(reng);
}

int main() {
  enum class Status {start, ip, won, lost, end};
  Status gamestat {Status::start};
  int points_to_make{0};
  while (Status::end != gamestat) {
    if (Status::won == gamestat) {
      std::cout << "You won." << std::endl;
      gamestat = Status::end;
    } else if (Status::lost == gamestat) {
      std::cout << "You lost." << std::endl;
      gamestat = Status::end;
    } else {
      std::cout << "Press ENTER to roll";
      std::getchar();
      int dice1{ roll_dice() }, dice2{ roll_dice() };
      int points{dice1 + dice2};
      std::cout << fmt::format("You rolled {} and {}.\n", dice1, dice2);
      if (Status::start == gamestat) {
        if (7 == points || 11 == points) {
          gamestat = Status::won;
        } else if (2 == points || 3 == points || 12 == points) {
          gamestat = Status::lost;
        } else {
          gamestat = Status::ip;
          points_to_make = points;
        }
      } else if (Status::ip == gamestat) {
        if (7 == points) {
          gamestat = Status::lost;
        } else if (points == points_to_make) {
          gamestat = Status::won;
        }
      }
    }
  }
  std::cout << "Bye." << std::endl;
  return 0;
}
