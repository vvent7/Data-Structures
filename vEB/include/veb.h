#ifndef VEB_H
#define VEB_H

#include <memory>
#include <climits>
#include <cstddef>
#include "_veb_base.h"

// ============VebNode============
class VebNode {
public:
  virtual ~VebNode() = default;
  virtual bool insert(int x) = 0;
  virtual bool remove(int x) = 0;
  virtual bool member(int x) = 0;
  virtual int successor(int x) = 0;
  virtual int predecessor(int x) = 0;
  virtual int minimum() = 0;
  virtual int maximum() = 0;
  virtual int extract_min() = 0;
};
// =================================

// ==========VebNodeInner==========
class VebNodeInner : public VebNode{
public:
  VebNodeInner();
  VebNodeInner(int u); //[0, u-1]
  ~VebNodeInner();

  bool insert(int x) override;
  bool remove(int x) override;
  bool member(int x) override;
  int successor(int x) override;
  int predecessor(int x) override;
  int minimum() override;
  int maximum() override;
  int extract_min() override;

private:
  int k, u, uSqrtUpper, uSqrtLower;
  // k: 2^k = u
  // u: universe size [0, u-1]
  // uSqrtUpper: number of clusters (size of summary)
  // uSqrtLower: number of elements in each cluster (size of cluster)

  int mi, mx;

  VebNode *summary;
  VebNode **clusters;

  // std::unique_ptr<VebNode> summary;
  // std::unique_ptr<VebNode[]> cluster;

  inline int high(int x);
  inline int low(int x);
  inline int index(int x, int y);
};
// =================================

// ===========VebNodeLeaf==========
class VebNodeLeaf : public VebNode{
public:
  VebNodeLeaf();
  VebNodeLeaf(int u); //[0, u-1]

  bool insert(int x) override;
  bool remove(int x) override;
  bool member(int x) override;
  int successor(int x) override;
  int predecessor(int x) override;
  int minimum() override;
  int maximum() override;
  int extract_min() override;

private:
  int u;
  unsigned long long values;
};
// =================================

// =============Veb===============
class Veb : public _veb_base{
public:
  static const int NIL = -1;
  static const int BASE_U = sizeof(unsigned long long) * __CHAR_BIT__;

  Veb();
  Veb(int u);

  size_t size();
  bool insert(int x) override;
  bool remove(int x) override;
  bool member(int x) override;
  int successor(int x) override;
  int predecessor(int x) override;
  int minimum() override;
  int maximum() override;
  int extract_min() override;

private:
  VebNode *root;
  size_t sz;
};
// =================================

#endif