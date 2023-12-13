#ifndef VEB_MULTI_INNER_H
#define VEB_MULTI_INNER_H

#include <climits>
#include <variant>
#include <memory>
#include "veb_multi/veb_multi_leaf.h"
#include "veb_multi/_veb_multi_node.h"

// =============VebInner=============
class VebMultiInner : public _veb_multi_node{
public:
  VebMultiInner();
  VebMultiInner(int u); //[0, u-1]
  ~VebMultiInner() final override = default;

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
  int k, u, uSqrtUpper, uSqrtLower;
  // k: 2^k = u
  // u: universe size [0, u-1]
  // uSqrtUpper: number of clusters (size of summary)
  // uSqrtLower: number of elements in each cluster (size of cluster)

  int mi, mx; //mi and mx are unique
  unsigned long long cntMi, cntMx;

  std::unique_ptr<_veb_multi_node> summary;
  std::unique_ptr<std::unique_ptr<_veb_multi_node>[]> clusters;
};
// ==================================

#endif