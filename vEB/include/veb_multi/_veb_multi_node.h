#ifndef _VEB_MULTI_NODE_H
#define _VEB_MULTI_NODE_H

#include <climits>
#include <utility>

// ==============_veb_multi_node==============
class _veb_multi_node {
public:
  static const int NIL = -1;
  static const int BASE_U = sizeof(unsigned long long) * __CHAR_BIT__;

  virtual ~_veb_multi_node() = default;
  virtual bool empty() const = 0; // true if empty
  virtual int minimum(unsigned long long *cnt = nullptr) const = 0; // value
  virtual int maximum(unsigned long long *cnt = nullptr) const = 0; // value
  virtual int member(int x) const = 0; // count
  virtual int successor(int x, unsigned long long *cnt = nullptr) const = 0; // value
  virtual int predecessor(int x, unsigned long long *cnt = nullptr) const = 0; // value
  virtual unsigned long long insert(int x, unsigned long long n = 1, unsigned long long *cnt = nullptr) = 0; // insertedCnt
  virtual unsigned long long remove(int x, unsigned long long n = ULLONG_MAX, unsigned long long *cnt = nullptr) = 0; // removedCnt
  virtual int extract_min(unsigned long long *cnt = nullptr) = 0; // extractedValue
};
// ===========================================

#endif