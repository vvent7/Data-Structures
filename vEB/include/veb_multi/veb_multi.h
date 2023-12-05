#ifndef VEB_MULTI_H
#define VEB_MULTI_H

#include <cstddef>
#include <climits>
#include <utility>
#include <memory>
#include "_veb_multi.h"

// ==============VebMulti==============
class VebMulti {
public:
  size_t size() const;
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
  size_t sz;
};
// ================================

#endif