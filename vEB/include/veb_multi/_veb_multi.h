#ifndef _VEB_MULTI_H
#define _VEB_MULTI_H

#include <climits>
#include <utility>

// ==============_veb==============
class _veb_multi {
public:
  static const int NIL = -1;
  static const int BASE_U = sizeof(unsigned long long) * __CHAR_BIT__;

  virtual ~_veb_multi() = default;
  virtual int minimum(int *cnt = nullptr) const = 0; // value
  virtual int maximum(int *cnt = nullptr) const = 0; // value
  virtual int member(int x) const = 0; // count
  virtual int successor(int x, int *cnt = nullptr) const = 0; // value
  virtual int predecessor(int x, int *cnt = nullptr) const = 0; // value
  virtual int insert(int x, int n = 1, int *cnt = nullptr) = 0; // insertedCnt
  virtual int remove(int x, int n = INT_MAX, int *cnt = nullptr) = 0; // removedCnt
  virtual int extract_min(int *cnt = nullptr) = 0; // extractedValue
};
// ================================

#endif