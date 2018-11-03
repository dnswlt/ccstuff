#include <iostream>

class CopyCtor {
public:
  CopyCtor(CopyCtor& other) {
    x = other.x;
    std::cout << "Copy ctor called\n";
  }
  CopyCtor(int x) : x(x) {}
private:
  int x;
};

int main() {
  CopyCtor c1{7};
  // Does not compile: no default ctor
  // CopyCtor c2;
  CopyCtor c2{c1};
  CopyCtor c3 = c2; // works, calls copy ctor
  c1 = c3; // works, calls compiler-generated copy operator=
}

