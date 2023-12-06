#ifndef VEB_MULTI_LEAF_H
#define VEB_MULTI_LEAF_H

#include <climits> //MAX
#include <memory> //unique_tr
#include "_veb_multi.h"

// =============VebInner=============
class VebMultiLeaf : public _veb_multi{
public:
  VebMultiLeaf();
  VebMultiLeaf(int u); //[0, u-1]
  ~VebMultiLeaf() final override = default;

  bool empty() const final override;
  int minimum(unsigned long long *cnt = nullptr) const final override;
  int maximum(unsigned long long *cnt = nullptr) const final override;
  int member(int x) const final override;
  int successor(int x, unsigned long long *cnt = nullptr) const final override;

  int predecessor(int x, unsigned long long *cnt = nullptr) const final override;
  unsigned long long insert(int x, unsigned long long n = 1, unsigned long long *cnt = nullptr) final override;
  unsigned long long remove(int x, unsigned long long n = ULLONG_MAX, unsigned long long *cnt = nullptr) final override;
  int extract_min(unsigned long long *cnt = nullptr) final override;

private:
  int u;
  unsigned long long values;
  std::unique_ptr<unsigned long long[]> cntValues;
};
// ==================================

#endif