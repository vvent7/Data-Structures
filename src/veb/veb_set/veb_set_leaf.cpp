#include "veb/veb_env.h" // key_bit_t 
#include "veb/veb_set/veb_set_leaf.h"

namespace veb{

  SetLeaf::SetLeaf():
    u(0), values(0){}

  SetLeaf::SetLeaf(key_bit_t u):
    u(u), values(0){ }

  inline bool SetLeaf::empty() const {
    return values == 0;
  }

  key_bit_t SetLeaf::minimum() const {
    if(values == 0) return NIL_KEY_BIT;
    return __builtin_ffsll(values)-1;
  }

  key_bit_t SetLeaf::maximum() const {
    if(values == 0) return NIL_KEY_BIT;
    return BASE_U - 1 - __builtin_clzll(values);
  }

  bool SetLeaf::member(key_bit_t x) const {
    if(x >= u) return false;
    return (values & (1ULL << x)) != 0;
  }

  key_bit_t SetLeaf::successor(key_bit_t x) const {
    if(x >= u-1) return NIL_KEY_BIT;
    unsigned long long mask = ~((1ULL << (x+1)) - 1);
    unsigned long long succ = values & mask;

    key_bit_t ans = __builtin_ffsll(succ);

    return ans > 0 ? ans-1 : NIL_KEY_BIT;
  }

  key_bit_t SetLeaf::predecessor(key_bit_t x) const {
    if(x >= u) return NIL_KEY_BIT;
    unsigned long long mask = (1ULL << x) - 1;
    unsigned long long pred = values & mask;

    if(pred == 0) return NIL_KEY_BIT;

    key_bit_t ans = __builtin_clzll(pred);
    
    return BASE_U - 1 - ans;
  }

  bool SetLeaf::insert(key_bit_t x){
    if(member(x)) return false;
    values |= (1ULL << x);
    return true;
  }

  bool SetLeaf::remove(key_bit_t x){
    if(!member(x)) return false;
    values &= ~(1ULL << x);
    return true;
  }

  key_bit_t SetLeaf::extract_min(){
    key_bit_t x = minimum();
    if(x != NIL_KEY_BIT) remove(x);
    return x;
  }

}
