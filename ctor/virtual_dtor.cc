#include <iostream>
#include <memory>

class Base {
  public:
    Base(int x) : x_{x} {}
    int x() const noexcept { return x_; }
  protected:
    ~Base() {
      std::cout << "Called ~Base()\n"; 
    };
  private:
    int x_;
};

class Sub : public Base {
  public:
    Sub(int x) : Base(x) {}
    int x2() const noexcept { return x() * x(); }
// Will call ~Base():
//~Sub() = default;
    ~Sub() { 
      std::cout << "Called ~Sub()\n";
    }
};

void DtorCallsBase() {
  Sub b(7); 
}

void foo(std::unique_ptr<Base> base_ptr) {
  
}

void foo(std::unique_ptr<Sub> sub_ptr) {
  
}

void bar(const Base& base) {
  std::cout << "bar: " << base.x() << "\n";
}

int main() {
  DtorCallsBase();
  // Works:
  auto sub_ptr = std::make_unique<Sub>(7);
  // Does not work:
  // std::unique_ptr<Base> base_ptr = std::make_unique<Sub>(7);
  bar(*sub_ptr);
  // Deletes sub_ptr:
  foo(std::move(sub_ptr));
  std::cout << "main done.\n";
}
