#include <iostream>

// Some experiments with dynamic_cast and static_cast
//

class Parent {
protected:
  virtual ~Parent() {}
};

class ChildA : public Parent {
private:
  int x_;
public:
  explicit ChildA(int x) : x_{x} {}
  int x() { return x_; }
};

class ChildB : public Parent {
private:
  double d_;
public:
  explicit ChildB(double d) : d_{d} {}
  double d() { return d_; }
};

int main() {
  int x{1};
  double d{0.5};
  int y = static_cast<int>(d); // cannot use dynamic_cast here: target is not pointer or reference
  std::cout << y << "\n";

  ChildA a{1};
  Parent *p_a = &a;
  ChildB b{0.5};
  Parent *p_b = &b;
  ChildA *ba = dynamic_cast<ChildA *>(p_b);
  if (ba == nullptr) {
    std::cout << "dynamic_cast returned nullptr\n"; // Yes, ba will be nullptr
  } else {
    std::cout << ba->x() << "\n"; // never reached
  }
  return 0; 
}

