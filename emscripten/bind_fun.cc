#include <iostream>
#include <emscripten.h>

class Tripler {
  public:
    Tripler(int x) : x_(x) {}
    int value() {
      return x_ * 3;
    }
  private:
    int x_;
};

// For this simple test, we use the "cwrap" way of calling our functions from JavaScript.
// Hence, we need to put them in an extern "C" block.
extern "C" {

EMSCRIPTEN_KEEPALIVE
int triple(int x) {
  return Tripler(x).value();
}

EMSCRIPTEN_KEEPALIVE
char *reverse(char *s) {
  
}

}  // extern

int main() {
  // std::cout << "triple(3): " << triple(3) << "\n";
  return 0;
}



