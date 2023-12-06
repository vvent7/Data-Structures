#ifndef VEB_MULTI_H
#define VEB_MULTI_H

#include <climits> //MAX
#include <memory> //unique_ptr
#include "_veb_multi.h"

// ==============VebMulti==============
class VebMulti {
public:
  VebMulti();
  VebMulti(int u); //[0, u-1]
  bool empty() const;
  int minimum(unsigned long long *cnt = nullptr) const; // value
  int maximum(unsigned long long *cnt = nullptr) const; // value
  int member(int x) const; // count
  int successor(int x, unsigned long long *cnt = nullptr) const; // value
  int predecessor(int x, unsigned long long *cnt = nullptr) const; // value
  unsigned long long insert(int x, unsigned long long n = 1, unsigned long long *cnt = nullptr); // insertedCnt
  unsigned long long remove(int x, unsigned long long n = ULLONG_MAX, unsigned long long *cnt = nullptr); // removedCnt
  int extract_min(unsigned long long *cnt = nullptr); // extractedValue

private:
  std::unique_ptr<_veb_multi> root;
};
// ================================

#endif