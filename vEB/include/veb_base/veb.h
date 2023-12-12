#ifndef VEB_H
#define VEB_H

#include <cstddef>
#include <memory>
#include "_veb.h"

// =============Veb===============
class Veb{
public:
  Veb();
  Veb(int u);

  size_t size() const;
  bool empty() const;
  int minimum() const;
  int maximum() const;
  bool member(int x) const;
  int successor(int x) const;
  int predecessor(int x) const;
  bool insert(int x);
  bool remove(int x);
  int extract_min();

private:
  std::unique_ptr<_veb> root;
  size_t sz;
};
// =================================

#endif