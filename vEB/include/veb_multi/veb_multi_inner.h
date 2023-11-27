#ifndef VEB_MULTI_INNER_H
#define VEB_MULTI_INNER_H

#include <climits>
#include "_veb_multi.h"

// =============VebInner=============
class VebMultiInner : public _veb_multi{
public:
  VebMultiInner();
  VebMultiInner(int u); //[0, u-1]
  ~VebMultiInner() final override;

  int minimum(int *cnt = nullptr) const final override;
  int maximum(int *cnt = nullptr) const final override;
  int member(int x) const final override;
  int successor(int x, int *cnt = nullptr) const final override;
  int predecessor(int x, int *cnt = nullptr) const final override;
  int insert(int x, int n = 1, int *cnt = nullptr) final override;
  int remove(int x, int n = INT_MAX, int *cnt = nullptr) final override;
  int extract_min(int *cnt = nullptr) final override;

private:
  int k, u, uSqrtUpper, uSqrtLower;
  // k: 2^k = u
  // u: universe size [0, u-1]
  // uSqrtUpper: number of clusters (size of summary)
  // uSqrtLower: number of elements in each cluster (size of cluster)

  int mi, mx;
  int cntMi;

  _veb_multi *summary;
  _veb_multi **clusters;
};
// ==================================

#endif