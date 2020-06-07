#include <iostream>
#include <vector>
#include <cstdlib>


std::vector<int> longest_increasing(const std::vector<int>& xs) {
  std::vector<int> p(xs.size());
  std::vector<int> m(xs.size() + 1);
  int l = 0;
  for (int i = 0; i < xs.size(); i++) {
    int lo = 1;
    int hi = l;
    // Set lo to the greatest j <= l such that
    // xs[m[j]] <= xs[i].
    while (lo <= hi) {
      int mid = (lo + hi + 1) / 2;
      if (xs[m[mid]] <= xs[i]) {
        lo = mid + 1;
      } else {
        hi = mid - 1;
      }
    }
    int k = lo;
    // Append xs[i] to its longest prefix and store predecessor.
    p[i] = m[k - 1];
    m[k] = i;
    if (k > l) {
      // Longest sequence seen so far.
      l = k;
    }
  }
  std::vector<int> seq(l);
  int k = m[l];
  for (int i = l - 1; i >= 0; i--) {
    seq[i] = xs[k];
    k = p[k];
  }
  return seq;
}

int main(int argc, char** argv) {
  std::vector<int> args;
  for (int i=1; i < argc; i++) {
    args.push_back(std::atoi(argv[i]));
  }

  std::cout << "Read " << args.size() << " items.\n";
  const auto seq = longest_increasing(args);
  std::cout << "Longest increasing subsequence has length " << 
    seq.size() << ":\n";
  for (int i = 0; i < seq.size(); i++) {
    std::cout << " " << seq[i];
  }
  std::cout << std::endl;
  return 0;
}
