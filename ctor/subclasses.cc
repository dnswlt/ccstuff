#include <iostream>

class Base {
  private:
    Base(int c); // not accessible for subclasses
  public:
    Base();
    virtual void foo(int c);
};


Base::Base() : Base(0) {
  std::cout << "Base()\n";
}

Base::Base(int c) {
  std::cout << "Base(int)\n";
}

void Base::foo(int c) {
  std::cout << "Base::foo(int)\n";
}

class Sub1 : public Base {
  public:
    Sub1();
    void foo(int c) override;
};

Sub1::Sub1() : Base() {
  std::cout << "Sub1()\n";
}

void Sub1::foo(int c) {
  std::cout << "Sub1::foo(int)\n";
}

int main() {
  Base b;
  b.foo(1);
  std::cout << "=========\n";
  Sub1 s1;
  Base &bs1 = s1;
  bs1.foo(2);
}
