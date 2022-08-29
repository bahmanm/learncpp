#include <iostream>
#include <gmpxx.h>
#include <iomanip>

int main() {
  mpf_class a{0}, b{0}, c{0};
  std::cout << "Solve polynomial ax²+bx+c=0." << std::endl;
  std::cout << "Enter a: ";
  std::cin >> a;
  std::cout << "Enter b: ";
  std::cin >> b;
  std::cout << "Enter c: ";
  std::cin >> c;

  std::cout << std::setprecision(2) << std::fixed;
  mpf_class delta{b * b - 4 * a * c};
  if (delta < 0.0) {
    std::cout << "Δ < 0 - no real answers" << std::endl;
  } else if (delta == 0.0) {
    mpf_class answer{-b / (2 * a)};
    std::cout << "Δ = 0 - single answer: " << answer << std::endl;
  } else {
    mpf_class sqrt_delta{0};
    mpf_sqrt(sqrt_delta.get_mpf_t(), delta.get_mpf_t());
    mpf_class answer1{(-b - sqrt_delta) / (2 * a)}, answer2{(-b + sqrt_delta) / (2 * a)};
    std::cout << "Δ > 0 - two answers: " << answer1 << ", " << answer2 << std::endl;
  }
  return 0;
}
