#include <algorithm> // min
#include <memory> //unique_ptr
#include "utils.h"
#include "veb/veb_env.h"
#include "veb/veb_multi/veb_multi_leaf.h"

namespace veb{

  MultiLeaf::MultiLeaf():
    u(0), values(0), cntValues(nullptr){}

  MultiLeaf::MultiLeaf(key_bit_t u):
    u(u), values(0),
    cntValues(std::make_unique<unsigned long long[]>(u)){ }

  inline bool MultiLeaf::empty() const {
    return values == 0;
  }

  key_bit_t MultiLeaf::minimum(unsigned long long *cnt) const {
    if(empty()) return deal_opt(cnt, 0), NIL_KEY_BIT;

    key_bit_t x = __builtin_ffsll(values)-1;
    
    return deal_opt(cnt, cntValues[x]), x;
  }

  key_bit_t MultiLeaf::maximum(unsigned long long *cnt) const {
    if(empty()) return deal_opt(cnt, 0), NIL_KEY_BIT;

    key_bit_t x = BASE_U - 1 - __builtin_clzll(values);
    
    return deal_opt(cnt, cntValues[x]), x;
  }

  unsigned long long MultiLeaf::member(key_bit_t x) const {
    if(x >= u) return 0;
    return cntValues[x];
  }

  key_bit_t MultiLeaf::successor(key_bit_t x, unsigned long long *cnt) const {
    if(x >= u-1) return deal_opt(cnt, 0), NIL_KEY_BIT;
    unsigned long long mask = ~((1ULL << (x+1)) - 1);
    unsigned long long succ = values & mask;

    key_bit_t ans = __builtin_ffsll(succ);

    return ans <= 0
      ? (deal_opt(cnt, 0),  NIL_KEY_BIT)
      : (deal_opt(cnt, cntValues[ans-1]), ans-1);
  }

  key_bit_t MultiLeaf::predecessor(key_bit_t x, unsigned long long *cnt) const {
    if(x >= u) return deal_opt(cnt, 0), NIL_KEY_BIT;
    unsigned long long mask = (1ULL << x) - 1;
    unsigned long long pred = values & mask;

    if(pred == 0) return deal_opt(cnt, 0), NIL_KEY_BIT;

    key_bit_t ans = __builtin_clzll(pred);
    key_bit_t predX = BASE_U - 1 - ans;
    return deal_opt(cnt, cntValues[predX]), predX;
  }

  unsigned long long MultiLeaf::insert(key_bit_t x, unsigned long long n, unsigned long long *cnt){
    if((x>=u) | (n<=0)) return deal_opt(cnt, 0), 0;
    
    values |= (1ULL << x);
    n = std::min(n, ULLONG_MAX - cntValues[x]);
    cntValues[x] += n;

    return deal_opt(cnt, cntValues[x]), n;
  }

  unsigned long long MultiLeaf::remove(key_bit_t x, unsigned long long n, unsigned long long *cnt){
    if((x>=u) | (n<=0)) return deal_opt(cnt, 0), 0;
    
    n = std::min(n, cntValues[x]);
    cntValues[x] -= n;
    if(cntValues[x] == 0) values &= ~(1ULL << x);
    
    return deal_opt(cnt, cntValues[x]), n;
  }

  key_bit_t MultiLeaf::extract_min(unsigned long long *cnt){
    if(empty()) return deal_opt(cnt, 0), NIL_KEY_BIT;
    key_bit_t x = minimum();
    return remove(x, 1, cnt), x;
  }

}