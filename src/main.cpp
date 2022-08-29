#include <iostream>
#include <cmath>
#include <iomanip>

int main() {
  double a{0.0}, b{0.0}, c{0.0};

  std::cout << "Solve polynomial ax²+bx+c=0." << std::endl;
  std::cout << "Enter a: ";
  std::cin >> a;
  std::cout << "Enter b: ";
  std::cin >> b;
  std::cout << "Enter c: ";
  std::cin >> c;

  std::cout << std::setprecision(2) << std::fixed;
  double delta{b * b - 4 * a * c};
  if (delta < 0.0) {
    std::cout << "Δ < 0 - no real answers" << std::endl;
  } else if (delta == 0.0) {
    double answer{-b / (2 * a)};
    std::cout << "Δ = 0 - single answer: " << answer << std::endl;
  } else {
    double sqrt_delta{std::sqrt(delta)};
    double answer1{(-b - sqrt_delta) / (2 * a)}, answer2{(-b + sqrt_delta) / (2 * a)} ;
    std::cout << "Δ > 0 - two answers: " << answer1 << ", " << answer2 << std::endl;
  }
  double sqrt_delta{std::sqrt(delta)};

}
