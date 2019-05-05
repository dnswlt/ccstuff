/*
 * The stepping stone model. Given an n*n matrix of creatures of k different
 * types ("colors"). In each round, a random creatures takes on the color of
 * one of its 8 neighboring creatures.
 *
 * The stepping stone model states that with a probability of 1, the model
 * converges to a world in which all creatures are of the same type.
 */

#include <vector>
#include <iostream>
#include <random>
#include <map>

namespace {

using Matrix = std::vector<std::vector<int>>;

void print_m(const Matrix& m) {
  for (int i=0; i<m.size(); i++) {
    for (int j=0; j<m[i].size(); j++) {
      std::cout << m[i][j];
    }
    std::cout << "\n";
  }
}

void print_freq(const Matrix& m) {
  std::map<int, int> freq;
  for (int i=0; i<m.size(); i++) {
    for (int j=0; j<m[i].size(); j++) {
      freq[m[i][j]]++;
    }
  }
  for (const auto& e : freq) {
    std::cout << e.first << ": " << e.second << "\n";
  }
}

std::default_random_engine& eng() {
  static std::default_random_engine e{};
  return e;
}

void round(Matrix& m) {
  const int n = m[0].size();
  std::uniform_int_distribution<int> r(0, 7);
  std::uniform_int_distribution<int> r_n(0, n-1);
  int c = r(eng());
  int i = 0;
  int j = 0;
  switch (c) {
    case 0:
     i = n-1; j = n-1; break;
    case 1:
     i = n-1; j = 0; break;
    case 2:
     i = n-1; j = 1; break;
    case 3:
     i = 0; j = n-1; break;
    case 4:
     i = 0; j = 1; break;
    case 5:
     i = 1; j = n-1; break;
    case 6:
     i = 1; j = 0; break;
    case 7:
     i = 1; j = 1; break;
  }
  int a = r_n(eng());
  int b = r_n(eng());
  m[a][b] = m[(a+i)%n][(b+j)%n];
}

bool all_same(const Matrix& m) {
  if (m.empty()) {
    return true;
  }
  if (m[0].empty()) {
    return true;
  }
  int v = m[0][0];
  for (int i=0; i<m.size(); i++) {
    for (int j=0; j<m[i].size(); j++) {
      if (m[i][j] != v) {
        return false;
      }
    }
  }
  return true;
}

void init_random() {
  std::random_device d;
  eng().seed(d());
}

}  // namespace


int main() {
  
  const int max_rounds = 1000000;
  const int k = 3;
  const int n = 10;
  init_random();

  std::uniform_int_distribution<int> r(0, k-1);
  Matrix m(n, std::vector<int>(n));

  for (int i=0; i<n; i++) {
    for (int j=0; j<n; j++) {
      m[i][j] = r(eng());
    }
  }
  print_m(m);

  int num_rounds = 0;
  while (num_rounds < max_rounds) {
    if (num_rounds % 500 == 0) {
      print_freq(m);
      std::cout << "\n";
    }
    round(m);
    num_rounds++;
    if (all_same(m)) {
      std::cout << "All creatures are the same.\n";
      break;
    }
  }
  std::cout << "After " << num_rounds << " rounds:\n";
  print_m(m);

}

