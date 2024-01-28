#ifndef VEB_MULTI_INNER_H
#define VEB_MULTI_INNER_H

#include <climits> // ULLONG_MAX
#include <memory> // unique_ptr
#include "veb/veb_env.h" // key_bit_t
#include "_veb_multi_node.h"

namespace veb{
  class MultiInner : public _multi_node{
  public:
    MultiInner();
    MultiInner(key_bit_t u); //[0, u-1]
    ~MultiInner() final override = default;

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
    key_bit_t k, u, uSqrtUpper, uSqrtLower;
    // k: 2^k = u
    // u: universe size [0, u-1]
    // uSqrtUpper: number of clusters (size of summary)
    // uSqrtLower: number of elements in each cluster (size of cluster)

    key_bit_t mi, mx; //mi and mx are unique
    unsigned long long cntMi, cntMx;

    std::unique_ptr<_multi_node> summary;
    std::unique_ptr<std::unique_ptr<_multi_node>[]> clusters;
  };
}

#endif