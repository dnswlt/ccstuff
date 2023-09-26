// Example WASM using "embind" style bindings of C++ classes.
//
// Compile with
// emcc -lembind -o embind_test.js embind_test.cc

#include <iostream>
#include <algorithm>
#include <string>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <emscripten/bind.h>

using namespace emscripten;
#endif  // __EMSCRIPTEN__

struct EmParams {
  std::string data;
  int timeout;
};

struct EmResult {
  std::string data;
  int len;
};

EmResult doSomething(EmParams p) {
  EmResult r;
  r.data = p.data;
  r.len = p.data.size();
  std::reverse(r.data.begin(), r.data.end());
  return r;
}

#ifdef __EMSCRIPTEN__
// Make input/output structs and global functions available in JavaScript.
EMSCRIPTEN_BINDINGS(em_request) {
  value_object<EmParams>("EmParams")
    .field("data", &EmParams::data)
    .field("timeout", &EmParams::timeout);
  value_object<EmResult>("EmResult")
    .field("data", &EmResult::data)
    .field("len", &EmResult::len);
  function("doSomething", &doSomething);
}
#endif  // __EMSCRIPTEN__

int main() {
  std::cout << "main: embind_test\n";
  return 0;
}

