#ifndef VEB_SET_INNER_H
#define VEB_SET_INNER_H

#include "veb/veb_env.h" // key_bit_t
#include "_veb_set_node.h" // _set_node

namespace veb{

  class SetInner : public _set_node{
  public:
    SetInner();
    SetInner(key_bit_t u); //[0, u-1]
    ~SetInner() final override;

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
    key_bit_t k, u, uSqrtUpper, uSqrtLower;
    // k: 2^k = u
    // u: universe size [0, u-1]
    // uSqrtUpper: number of clusters (size of summary)
    // uSqrtLower: number of elements in each cluster (size of cluster)

    key_bit_t mi, mx;

    _set_node *summary;
    _set_node **clusters;
  };

};

#endif