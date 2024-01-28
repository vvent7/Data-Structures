#ifndef VEB_MULTI_LEAF_H
#define VEB_MULTI_LEAF_H

#include <climits> // ULLONG_MAX
#include <memory> //unique_tr
#include "veb/veb_env.h" // key_bit_t
#include "_veb_multi_node.h"

namespace veb{
  class MultiLeaf : public _multi_node{
  public:
    MultiLeaf();
    MultiLeaf(key_bit_t u); //[0, u-1]
    ~MultiLeaf() final override = default;

    bool empty() const final override;
    key_bit_t minimum(unsigned long long *cnt = nullptr) const final override;
    key_bit_t maximum(unsigned long long *cnt = nullptr) const final override;
    unsigned long long member(key_bit_t x) const final override;
    key_bit_t successor(key_bit_t x, unsigned long long *cnt = nullptr) const final override;

    key_bit_t predecessor(key_bit_t x, unsigned long long *cnt = nullptr) const final override;
    unsigned long long insert(key_bit_t x, unsigned long long n = 1, unsigned long long *cnt = nullptr) final override;
    unsigned long long remove(key_bit_t x, unsigned long long n = ULLONG_MAX, unsigned long long *cnt = nullptr) final override;
    key_bit_t extract_min(unsigned long long *cnt = nullptr) final override;

  private:
    key_bit_t u;
    unsigned long long values;
    std::unique_ptr<unsigned long long[]> cntValues;
  };
}

#endif