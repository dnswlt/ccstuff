#include <iostream>
#include <string>

struct TwoInt32 {
    int32_t a;
    int32_t b;
};

struct ThreeInt32 {
    int32_t a;
    int32_t b;
    int32_t c;
};

struct ThreeStringsAndAnInt32 {
    std::string a;
    std::string b;
    std::string c;
    int32_t n;
};

class VirtualInt64 {
  public:
    virtual int Foo() {
        return 0;
    }
  private:
    int64_t x_;
};


class ConcreteInt64 {
  public:
   int Foo() {
        return 0;
    }
  private:
    int64_t x_;
};

int main() {
    std::cout << "sizeof(std::string): " << sizeof(std::string) << "\n";
    std::cout << "string().capacity(): " << std::string().capacity() << "\n";
    std::string flight_key = "HAM-MUC-LH-7798";
    std::cout << "flight_key.size(): " << flight_key.size() << "\n";
    std::cout << "sizeof(ThreeStringsAndAnInt32): " << sizeof(ThreeStringsAndAnInt32) << "\n";
    std::cout << "sizeof(int): " << sizeof(int) << "\n";
    std::cout << "sizeof(long): " << sizeof(long) << "\n";
    std::cout << "sizeof(double): " << sizeof(double) << "\n";
    std::cout << "sizeof(void*): " << sizeof(void*) << "\n";
    std::cout << "sizeof(struct TwoInt32): " << sizeof(TwoInt32) << "\n";
    std::cout << "sizeof(struct ThreeInt32): " << sizeof(ThreeInt32) << "\n";
    std::cout << "sizeof(class VirtualInt64): " << sizeof(VirtualInt64) << "\n";
    std::cout << "sizeof(class ConcreteInt64): " << sizeof(ConcreteInt64) << "\n";
    return 0;
}