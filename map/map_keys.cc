/*
 * Can you use a user-defined class as a key in a map without
 * defining a comparison function? 
 *
 * Answer: no, you cannot. You need to define operator<
 *
 * Can you use an unordered_map
 * without defining any hash function?
 */
#include <map>
#include <unordered_map>
#include <iostream>

class Widget {
  public:
    int x_;
    int y_;
    Widget(int x, int y) : x_{x}, y_{y} {}
    // Required to be able to use Widget as an unordered_map key.
    bool operator==(const Widget& other) const {
      return x_ == other.x_ && y_ == other.y_;
    }
};

namespace std {
  
template<>
struct hash<Widget> {
  size_t operator()(const Widget& w) const {
    size_t h = 17;
    h = h * 31 + w.x_;
    h = h * 31 + w.y_;
    return h;
  }
};

}  // namespace std

// Required to be able to use Widget as a map key.
bool operator<(const Widget& w1, const Widget& w2) {
  if (w1.x_ < w2.x_) {
    return true;
  }
  return w1.x_ == w2.x_ && w1.y_ < w2.y_;
}

void ordered_map() {
  std::map<Widget, int> widget_count;
  widget_count[Widget(1, 0)]++;

  std::cout << "count(1,0) is " << widget_count[Widget(1, 0)] << "\n";
  std::cout << "count(0,1) is " << widget_count[Widget(0, 1)] << "\n";
}

void unordered_map() {
  std::unordered_map<Widget, int> widget_count;
  widget_count[Widget(1, 0)]++;

  std::cout << "count(1,0) is " << widget_count[Widget(1, 0)] << "\n";
  std::cout << "count(0,1) is " << widget_count[Widget(0, 1)] << "\n";

}

int main() {
  ordered_map();
  unordered_map();
  return 0;
}

