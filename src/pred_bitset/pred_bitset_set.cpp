#include <cstddef> //size_t
#include <vector> //vector
#include "pred_bitset/pred_bitset_env.h" //namespace pred_bitset
#include "pred_bitset/pred_bitset_set.h"

namespace pred_bitset{
  Set::Set():
    bitset(), sz(0),
    max_key(NIL_KEY_BIT), mi(NIL_KEY_BIT), mx(NIL_KEY_BIT){}

  Set::Set(key_bit_t max_key):
    bitset(max_key + 1, false), sz(0),
    max_key(max_key), mi(max_key), mx(0){}

  size_t Set::size() const {
    return sz;
  }

  bool Set::empty() const {
    return sz == 0;
  }

  key_bit_t Set::minimum() {
    if(sz == 0) return NIL_KEY_BIT;
    if(member(mi)) return mi;
    for(key_bit_t x = mi; x < bitset.size(); ++x)
      if(bitset[x]) return mi = x;
    mi = max_key;
    return NIL_KEY_BIT;
  }

  key_bit_t Set::maximum() {
    if(sz == 0) return NIL_KEY_BIT;
    if(member(mx)) return mx;
    for(key_bit_t x = mx; x > 0; --x)
      if(bitset[x]) return mx = x;
    mx = 0;
    return bitset[0] ? mx : NIL_KEY_BIT;
  }

  bool Set::member(key_bit_t x) const {
    return x < bitset.size() && bitset[x];
  }

  key_bit_t Set::successor(key_bit_t x) const {
    if(x >= bitset.size()) return NIL_KEY_BIT;
    for(++x; x < bitset.size(); ++x)
      if(bitset[x]) return x;
    return NIL_KEY_BIT;
  }

  key_bit_t Set::predecessor(key_bit_t x) const {
    if(x >= bitset.size() || x==0) return NIL_KEY_BIT;
    for(--x; x > 0; --x)
      if(bitset[x]) return x;
    return bitset[0] ? 0 : NIL_KEY_BIT;
  }

  bool Set::insert(key_bit_t x){
    if(x >= bitset.size()) return false;
    if(bitset[x]) return false;
    bitset[x] = true;
    ++sz;
    if(x < mi) mi = x;
    if(x > mx) mx = x;
    return true;
  }

  bool Set::remove(key_bit_t x){
    if(x >= bitset.size()) return false;
    if(!bitset[x]) return false;
    bitset[x] = false;
    --sz;
    return true;
  }

  key_bit_t Set::extract_min(){
    if(sz == 0) return NIL_KEY_BIT;
    key_bit_t x = minimum();
    remove(x);
    return x;
  }
}
