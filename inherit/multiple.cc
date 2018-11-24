#include <iostream>
#include "multiple.h"

C::C(int x) : x_{x} {}

void C::foo() {
  std::cout << "C::foo()\n";
}

D::D(int x) : x_{x} {}

void D::foo() {
  std::cout << "D::foo()\n";
}

E::E(int x1, int x2) : C{x1}, D{x2} {}

int main() {
  E e{1, 2};
  // e.foo(); // does not compile: error: request for member 'foo' is ambiguous
  e.D::foo(); // explicitly state which method you mean 
  E *ep = &e;
  ep->D::foo(); // explicit qualification also works for pointers
}

