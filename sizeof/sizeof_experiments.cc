#include <iostream>
#include <string>

struct TwoInt32
{
  int32_t a;
  int32_t b;
};

struct ThreeInt32
{
  int32_t a;
  int32_t b;
  int32_t c;
};

struct ThreeStringsAndAnInt32
{
  std::string a;
  std::string b;
  std::string c;
  int32_t n;
};

class VirtualInt64
{
public:
  virtual int Foo()
  {
    return 0;
  }

private:
  int64_t x_;
};

class ConcreteInt64
{
public:
  int Foo()
  {
    return 0;
  }

private:
  int64_t x_;
};

int32_t some_fn()
{
  return 7;
}

int main()
{
  // Strings
  std::cout << "sizeof(std::string): " << sizeof(std::string) << "\n";
  std::cout << "string().capacity(): " << std::string().capacity() << "\n";
  std::string flight_key = "HAM-MUC-LH-7798";
  std::cout << "flight_key.size(): " << flight_key.size() << "\n";

  // Primitive types
  std::cout << "sizeof(int): " << sizeof(int) << "\n";
  std::cout << "sizeof(long): " << sizeof(long) << "\n";
  std::cout << "sizeof(double): " << sizeof(double) << "\n";
  std::cout << "sizeof(void*): " << sizeof(void *) << "\n";

  // Structs
  std::cout << "sizeof(ThreeStringsAndAnInt32): " << sizeof(ThreeStringsAndAnInt32) << "\n";
  std::cout << "sizeof(struct TwoInt32): " << sizeof(TwoInt32) << "\n";
  std::cout << "sizeof(struct ThreeInt32): " << sizeof(ThreeInt32) << "\n";
  std::cout << "sizeof(class VirtualInt64): " << sizeof(VirtualInt64) << "\n";
  std::cout << "sizeof(class ConcreteInt64): " << sizeof(ConcreteInt64) << "\n";

  // Functions and lambdas
  std::cout << "sizeof(&some_fn): " << sizeof(&some_fn) << "\n";
  auto lambda_pure = [](int32_t x) { return x * x; };
  std::cout << "sizeof(lambda_pure): " << sizeof(lambda_pure) << "\n";
  int32_t v[10] = {0};
  auto lambda_capture_int32_t_arr_10 = [v](int32_t i) { return v[i]; };
  std::cout << "sizeof(lambda_capture_int32_t_arr_10): " << sizeof(lambda_capture_int32_t_arr_10) << "\n";
  auto lambda_capture_int32_t_arr_ref = [&v](int32_t i) { return v[i]; };
  std::cout << "sizeof(lambda_capture_int32_t_arr_ref): " << sizeof(lambda_capture_int32_t_arr_ref) << "\n";

  return 0;
}