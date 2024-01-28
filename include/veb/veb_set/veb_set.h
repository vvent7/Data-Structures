#ifndef VEB_SET_H
#define VEB_SET_H

#include <cstddef> //size_t
#include <memory> //unique_ptr
#include "veb/veb_env.h" // key_bit_t
#include "_veb_set_node.h" // _set_node

namespace veb{

  class Set{
  public:
    Set();
    Set(key_bit_t u);

    size_t size() const;
    bool empty() const;
    key_bit_t minimum() const;
    key_bit_t maximum() const;
    bool member(key_bit_t x) const;
    key_bit_t successor(key_bit_t x) const;
    key_bit_t predecessor(key_bit_t x) const;
    bool insert(key_bit_t x);
    bool remove(key_bit_t x);
    key_bit_t extract_min();

  private:
    std::unique_ptr<_set_node> root;
    size_t sz;
  };

}


#endif