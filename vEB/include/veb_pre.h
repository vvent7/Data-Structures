
#include <vector>
#include <cstddef>

// van Emde Boas (preliminary)
class VebPre {
private:
  const int k, u, uSqrt;
  int n;
  // k: universe size 'u' is 2^(2*k), summary and clusters sizes are 2^k
  // u: universe size [0, u-1]
  // uSqrt: number of clusters (size of summary)
  // n: number of elements in the set

  std::vector<bool> a;
  std::vector<bool> summary;

public:
  // constructor for universe size u [0, u-1]
  VebPre(size_t u);

  void insert(int x);
  void remove(int x);
  size_t size();
  bool member(int x);
  int successor(int x);
  int predecessor(int x);
  int minimum();
  int maximum();
  int extract_min();
};