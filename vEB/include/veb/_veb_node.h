#ifndef _VEB_NODE_H
#define _VEB_NODE_H

#include <climits> // __CHAR_BIT__

// ==============_veb_node==============
class _veb_node {
public:
  static constexpr int NIL = -1;
  static constexpr int BASE_U = sizeof(unsigned long long) * __CHAR_BIT__;

  virtual ~_veb_node() = default;
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