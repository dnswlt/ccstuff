#include <iostream>
#include <type_traits>

template<typename T>
std::enable_if_t<std::is_floating_point_v<T>> foo(T val) {
    std::cout << "Floaty floatsen: " << val << "\n";
}

template<typename T>
std::enable_if_t<!std::is_floating_point_v<T>> foo(T val) {
    std::cout << "Other stuff: " << val << "\n";
}

int main() {
    foo(3.1);
    foo("foosen");
    return 0;
}