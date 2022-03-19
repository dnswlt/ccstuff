#include <iostream>

enum EnumOne {
    kFoo = 0,
    kBar = 2,
};


enum EnumTwo {
    kBaz = 0,
    kQuz = 2,
};

int Foo(EnumOne e) {
    return 1;
}

int Foo(EnumTwo e) {
    return 2;
}

int Foo(int32_t e) {
    return -e;
}

int main() {
    int32_t n = 17;
    std::cout << "EnumOne: " << Foo(kFoo) << "\n";
    std::cout << "EnumTwo: " << Foo(kBaz) << "\n";
    std::cout << "int32_t: " << Foo(n) << "\n";
    return 0;
}