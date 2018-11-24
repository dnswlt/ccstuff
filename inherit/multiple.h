
class C {
  int x_;
public:
  C(int x);
  void foo();
};

class D {
  int x_;
public:
  D(int x);
  void foo();
};

class E : public C, public D {
public:
  E(int x1, int x2);
};

