#ifndef VEB_PRE_H
#define VEB_PRE_H

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

  bool insert(int x) override;
  bool remove(int x) override;
  int size();
  bool member(int x) override;
  int successor(int x) override;
  int predecessor(int x) override;
  int minimum() override;
  int maximum() override;
  int extract_min() override;
};

#endif