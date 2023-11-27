#ifndef VEB_H
#define VEB_H

#include <cstddef>
#include "_veb.h"

// =============Veb===============
class Veb{
public:
  Veb();
  Veb(int u);
  ~Veb();

  size_t size();
  bool insert(int x);
  bool remove(int x);
  bool member(int x);
  int successor(int x);
  int predecessor(int x);
  int minimum();
  int maximum();
  int extract_min();

private:
  _veb *root;
  size_t sz;
};
// =================================

#endif