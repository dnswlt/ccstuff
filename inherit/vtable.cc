#include <iostream>

using namespace std;

class Foo {
  public:
    virtual int f() { return 0; }
    virtual ~Foo() = default;
};

class Bar {
  public:
    virtual int g() { return 1; }
};

class Baz : public Foo, public Bar {
  public:
    int g() override { return 2; }
};

int main()
{
    Baz baz;
    Bar* bar = &baz;
    Foo* foo = &baz;
    bool equal_addr_foo = static_cast<void*>(&baz) == static_cast<void*>(foo);
    bool equal_addr_bar = static_cast<void*>(&baz) == static_cast<void*>(bar);
    cout << "Same address (foo): " << equal_addr_foo << endl;
    cout << "Same address (bar): " << equal_addr_bar << endl;

    return 0;
}
