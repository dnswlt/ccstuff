// Fun with variadic templates.
#include <iostream>
#include <string>
#include <typeinfo>

template <typename Arg>
void PrintAll(Arg arg) {
  std::cout << arg << "\n";
}

template <typename Arg, typename... Args>
void PrintAll(Arg arg, Args... args) {
  std::cout << arg << ", ";
  PrintAll(args...); 
}

int main() {
  const std::string x = "fugasi";
  const int y = 17;
  PrintAll(x, y);
}
