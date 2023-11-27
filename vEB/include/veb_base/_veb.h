#ifndef _VEB_H
#define _VEB_H

#include <climits>

// ==============_veb==============
class _veb {
public:
  static const int NIL = -1;
  static const int BASE_U = sizeof(unsigned long long) * __CHAR_BIT__;

  virtual ~_veb() = default;
  virtual int minimum() const = 0;
  virtual int maximum() const = 0;
  virtual bool member(int x) const = 0;
  virtual int successor(int x) const = 0;
  virtual int predecessor(int x) const = 0;
  virtual bool insert(int x) = 0;
  virtual bool remove(int x) = 0;
  virtual int extract_min() = 0;
};
// ================================

#endif