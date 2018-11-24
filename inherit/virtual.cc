#include <iostream>

// Virtual base class and some subclasses

class Base {
public:
  virtual void Foo() const;
};

class SubA : public Base {
public:
  // Holy moly: Foo defined with const and non const signature o_O
  void Foo() const override;
  void Foo();
};

void Base::Foo() const {
  std::cout << "Base::Foo() const\n";
}

void SubA::Foo() const {
  std::cout << "SubA::Foo() const\n";
}

void SubA::Foo() {
  std::cout << "SubA::Foo()\n";
}

void CallFoo(const Base& b) {
  b.Foo(); // calls the non-const version in any case, whether b :: SubA or b :: Base
}

int main() {
  SubA a;
  const SubA kA;
  CallFoo(a);
  a.Foo(); // calls the non-const version
  kA.Foo(); // calls the const version
}


