#ifndef _VEB_SET_NODE_H
#define _VEB_SET_NODE_H

#include "veb/veb_env.h" // key_bit_t

namespace veb{

  class _set_node {
  public:
    virtual ~_set_node() = default;
    virtual bool empty() const = 0;
    virtual key_bit_t minimum() const = 0;
    virtual key_bit_t maximum() const = 0;
    virtual bool member(key_bit_t x) const = 0;
    virtual key_bit_t successor(key_bit_t x) const = 0;
    virtual key_bit_t predecessor(key_bit_t x) const = 0;
    virtual bool insert(key_bit_t x) = 0;
    virtual bool remove(key_bit_t x) = 0;
    virtual key_bit_t extract_min() = 0;
  };

}

#endif