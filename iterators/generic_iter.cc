#include <vector>
#include <iostream>
#include <set>

// This example shows how to define a template function that can iterate over 
// any iterable sequence of a given type (Widget).

// Let's use a Widget instead of plain int's to make the example a bit more "interesting".
struct Widget {
  Widget(int x) : x{x} {}
  int x = 0;
};

// Required to put Widget into a std::set.
bool operator<(const Widget& a, const Widget& b) {
  return a.x < b.x;
}

// And here comes our template function. It takes, in compliance with functions from the STL,
// a pair of iterators as inputs, advances an auxiliary iterator from begin_it till end_it
// (exclusive) and aggregates Widget.x values.
// In fact, this template function does not depend on Widget at all, but only requires
// that the elements iterated over have an int-convertible field "x".
template<typename Iter>
int sum_it(const Iter begin_it, const Iter end_it) {
  int sum = 0;
  auto it = begin_it;
  while (it != end_it) {
    sum += it->x;
    it++;
  }
  return sum;
}

// Test the function by feeding it std::vector and std::set iterators.
int main(int argc, char** argv) {
  std::vector<Widget> xs{{.x = 1}, {.x = 2}, {.x = 3}};
  std::set<Widget> ys{4, 5, 6};
  std::cout << "Sum(xs) = " << sum_it(xs.begin(), xs.end()) << "\n";
  std::cout << "Sum(ys) = " << sum_it(ys.begin(), ys.end()) << "\n"; 
}

