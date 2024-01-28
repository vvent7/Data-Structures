#ifndef VEB_MULTI_H
#define VEB_MULTI_H

#include <climits> //ULLONG_MAX
#include <memory> //unique_ptr
#include "veb/veb_env.h" //key_bit_t
#include "_veb_multi_node.h"

namespace veb{

  class Multi {
  public:
    Multi();
    Multi(key_bit_t u); //[0, u-1]
    bool empty() const;
    key_bit_t minimum(unsigned long long *cnt = nullptr) const; // value
    key_bit_t maximum(unsigned long long *cnt = nullptr) const; // value
    unsigned long long member(key_bit_t x) const; // count
    key_bit_t successor(key_bit_t x, unsigned long long *cnt = nullptr) const; // value
    key_bit_t predecessor(key_bit_t x, unsigned long long *cnt = nullptr) const; // value
    unsigned long long insert(key_bit_t x, unsigned long long n = 1, unsigned long long *cnt = nullptr); // insertedCnt
    unsigned long long remove(key_bit_t x, unsigned long long n = ULLONG_MAX, unsigned long long *cnt = nullptr); // removedCnt
    key_bit_t extract_min(unsigned long long *cnt = nullptr); // extractedValue

  private:
    std::unique_ptr<_multi_node> root;
  };
  
}


#endif