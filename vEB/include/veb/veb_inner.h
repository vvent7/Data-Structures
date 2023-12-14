#ifndef VEB_INNER_H
#define VEB_INNER_H

#include "_veb_node.h" // _veb_node

// =============VebInner=============
class VebInner : public _veb_node{
public:
  VebInner();
  VebInner(int u); //[0, u-1]
  ~VebInner() final override;

  int minimum() const final override;
  int maximum() const final override;
  bool member(int x) const final override;
  int successor(int x) const final override;
  int predecessor(int x) const final override;
  bool insert(int x) final override;
  bool remove(int x) final override;
  int extract_min() final override;

private:
  int k, u, uSqrtUpper, uSqrtLower;
  // k: 2^k = u
  // u: universe size [0, u-1]
  // uSqrtUpper: number of clusters (size of summary)
  // uSqrtLower: number of elements in each cluster (size of cluster)

  int mi, mx;

  _veb_node *summary;
  _veb_node **clusters;
};
// ==================================

#endif