#include <iostream>
#include <string>

int main() {
  std::string input;
  const std::string correctPassword = "password";

  std::cout << "Enter your password: ";
  std::cin >> input;

  if(input == correctPassword) {
    std::cout << "Good" << std::endl;
  } else {
    std::cout << "Bad" << std::endl;
  }

  return 0;
}
