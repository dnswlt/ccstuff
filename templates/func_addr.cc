// A template can accept a function as a (value, not type) parameter.
// In this case, the instantiated template does not deref a function
// pointer at all, but calls the function directly.
//
// It's an interesting way to parameterize a class by a specific function
// and still keep the class serializable (so you can ship it to workers for
// execution) - there is no need to encode a function pointer at all.

#include <iostream>
#include <string>

template <typename T, void Fn(const T&)>
class Processor {
 public:
  void Process(T elem) { Fn(elem); }
};

void ProcessFn(const std::string& x) {
  std::cout << "Processing " << x << "\n";
}

int main() {
  Processor<std::string, &ProcessFn> p;
  p.Process("foo");
  return 0;
}
