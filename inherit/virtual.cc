#include <iostream>

class Base {
public:
  virtual void Foo() const;
};

class SubA : public Base {
  void Foo() const;
};

void Base::Foo() const {
  std::cout << "Base::Foo()\n";
}

void SubA::Foo() const {
  std::cout << "SubA::Foo()\n";
}

void CallFoo(const Base& b) {
  b.Foo();
}

int main() {
  SubA a;
  CallFoo(a);
}


