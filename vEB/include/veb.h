#ifndef VEB_H
#define VEB_H

#include <memory>
#include "_veb_base.h"

class Veb : public _veb_base{
public:
  static const int NIL = -1;

  Veb();
  Veb(int u); //[0, u-1]

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
  // k: universe size 'u' is 2^k
  // u: universe size [0, u-1]
  // uSqrtUpper: number of clusters (size of summary)
  // uSqrtLower: number of elements in each cluster (size of cluster)

  int mi, mx;
  std::unique_ptr<Veb> summary;
  std::unique_ptr<Veb[]> cluster;

  inline int high(int x);
  inline int low(int x);
  inline int index(int x, int y);
};

#endif