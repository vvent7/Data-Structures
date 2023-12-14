#ifndef VEB_LEAF_H
#define VEB_LEAF_H

#include "_veb_node.h" // _veb_node

// =============VebLeaf=============
class VebLeaf : public _veb_node{
public:
  VebLeaf();
  VebLeaf(int u); //[0, u-1]
  ~VebLeaf() final override = default;

  int minimum() const final override;
  int maximum() const final override;
  bool member(int x) const final override;
  int successor(int x) const final override;
  int predecessor(int x) const final override;
  bool insert(int x) final override;
  bool remove(int x) final override;
  int extract_min() final override;

private:
  int u;
  unsigned long long values;
};
// =================================

#endif