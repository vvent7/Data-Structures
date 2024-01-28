#ifndef _VEB_MULTI_NODE_H
#define _VEB_MULTI_NODE_H

#include <climits> // ULLONG_MAX
#include "veb/veb_env.h" // key_bit_t

namespace veb{
  class _multi_node {
  public:
    virtual ~_multi_node() = default;
    virtual bool empty() const = 0; // true if empty
    virtual key_bit_t minimum(unsigned long long *cnt = nullptr) const = 0; // value
    virtual key_bit_t maximum(unsigned long long *cnt = nullptr) const = 0; // value
    virtual unsigned long long member(key_bit_t x) const = 0; // count
    virtual key_bit_t successor(key_bit_t x, unsigned long long *cnt = nullptr) const = 0; // value
    virtual key_bit_t predecessor(key_bit_t x, unsigned long long *cnt = nullptr) const = 0; // value
    virtual unsigned long long insert(key_bit_t x, unsigned long long n = 1, unsigned long long *cnt = nullptr) = 0; // insertedCnt
    virtual unsigned long long remove(key_bit_t x, unsigned long long n = ULLONG_MAX, unsigned long long *cnt = nullptr) = 0; // removedCnt
    virtual key_bit_t extract_min(unsigned long long *cnt = nullptr) = 0; // extractedValue
  };
}

#endif