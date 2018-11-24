#include <iostream>

// Virtual classes contain at least a pointer into the class's vtable
// On my x64 machine, sizeof(C) == 8, sizeof(D) == 16

class C {
  int x;
  int y;
};

class D {
  int x;
  int y;
  virtual int foo();
  virtual double bar();
};

int main() {
  std::cout << "sizeof(C) == " << sizeof(C) << "\n";
  std::cout << "sizeof(D) == " << sizeof(D) << "\n";
}

