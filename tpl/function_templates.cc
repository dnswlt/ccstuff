#include <iostream>
#include <string>

template <typename T>
int cmp(T x, T y) {
  if (x == y) {
    return 0;
  } else if (x < y) {
    return -1;
  } else {
    return 1;
  }
}

void use_cmp_int(int a, int b) {
  cmp(a, b);
}

void use_cmp_string(std::string a, std::string b) {
  cmp(a, b);
}

class Widget {
private:
  int x_;
public:
  int x() const {
    return x_;
  }
  Widget(int x) : x_{x} {}
};

// We need lekker == and < on Widget to be able to instantiate cmp<Widget>.
bool operator==(const Widget& a, const Widget& b) {
  return a.x() == b.x();
}

bool operator<(const Widget& a, const Widget& b) {
  return a.x() < b.x();
}

void use_cmp_Widget(const Widget& a, const Widget& b) {
  cmp(a, b);
}

void use_cmp_Widget_value() {
  // Works, uses the const Widget& operators
  cmp(Widget(7), Widget(8));
}

