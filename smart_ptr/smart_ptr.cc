#include <iostream>
#include <memory>

class Widget {
private:
  int x_;
public:
  inline int x();
  Widget(int x);
  ~Widget();
};

using UPWidget = std::unique_ptr<Widget>;

int Widget::x() {
  return x_;
}

Widget::Widget(int x) : x_{x} {
  std::cout << "Widget(" << x_ << ") constructed\n";
}

Widget::~Widget() { 
  std::cout << "Widget(" << x_ << ") destructed\n"; 
}

void ProcessWidget(UPWidget w) {
  std::cout << "Processing Widget(" << w->x() << ")\n";
}

int main() {
  auto w1 = std::make_unique<Widget>(3);
  // auto w2 = std::move(w1);
  ProcessWidget(std::move(w1));
  if (w1 != nullptr) {
    std::cout << "Expected w1 to be set to nullptr\n";
    return 1;
  }

}

