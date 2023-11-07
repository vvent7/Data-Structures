
#include <vector>
#include <cstddef>
#include "_veb_base.h"

// van Emde Boas (preliminary)
class VebPre : public _veb_base{
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
  VebPre(int u);

  bool insert(int x);
  bool remove(int x);
  int size();
  bool member(int x);
  int successor(int x);
  int predecessor(int x);
  int minimum();
  int maximum();
  int extract_min();
};