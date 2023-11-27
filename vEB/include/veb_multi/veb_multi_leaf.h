#ifndef VEB_MULTI_LEAF_H
#define VEB_MULTI_LEAF_H

#include <climits>
#include <utility>
#include "_veb_multi.h"

// =============VebInner=============
class VebMultiLeaf : public _veb_multi{
public:
  VebMultiLeaf();
  VebMultiLeaf(int u); //[0, u-1]
  ~VebMultiLeaf() final override;

  int minimum(int *cnt = nullptr) const final override;
  int maximum(int *cnt = nullptr) const final override;
  int member(int x) const final override;
  int successor(int x, int *cnt = nullptr) const final override;
  int predecessor(int x, int *cnt = nullptr) const final override;
  int insert(int x, int n = 1, int *cnt = nullptr) final override;
  int remove(int x, int n = INT_MAX, int *cnt = nullptr) final override;
  int extract_min(int *cnt = nullptr) final override;

private:
  int u;
  unsigned long long values;
  int *cntValues;
};
// ==================================

#endif