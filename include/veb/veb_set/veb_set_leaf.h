#ifndef VEB_SET_LEAF_H
#define VEB_SET_LEAF_H

#include "veb/veb_env.h" // key_bit_t
#include "_veb_set_node.h" // _set_node

namespace veb{
  
  class SetLeaf : public _set_node{
  public:
    SetLeaf();
    SetLeaf(key_bit_t u); //[0, u-1]
    ~SetLeaf() final override = default;

    bool empty() const final override;
    key_bit_t minimum() const final override;
    key_bit_t maximum() const final override;
    bool member(key_bit_t x) const final override;
    key_bit_t successor(key_bit_t x) const final override;
    key_bit_t predecessor(key_bit_t x) const final override;
    bool insert(key_bit_t x) final override;
    bool remove(key_bit_t x) final override;
    key_bit_t extract_min() final override;

  private:
    key_bit_t u;
    unsigned long long values;
  };
  
}

#endif