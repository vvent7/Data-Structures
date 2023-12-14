#ifndef VEB_H
#define VEB_H

#include <cstddef> //size_t
#include <memory> //unique_ptr
#include "_veb_node.h" // _veb_node

// =============Veb===============
class Veb{
public:
  static constexpr int NIL = _veb_node::NIL;
  static constexpr int BASE_U = _veb_node::BASE_U;

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
  std::unique_ptr<_veb_node> root;
  size_t sz;
};
// =================================

#endif