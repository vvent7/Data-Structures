#include <cstddef>
#include <memory>
#include "utils.h"
#include "veb/veb_env.h"
#include "veb/veb_set/_veb_set_node.h"
#include "veb/veb_set/veb_set_inner.h"
#include "veb/veb_set/veb_set_leaf.h"
#include "veb/veb_set/veb_set.h"

namespace veb{

  Set::Set():
    root(nullptr), sz(0){}

  Set::Set(key_bit_t u){
    if(u > BASE_U)
      root = std::make_unique<SetInner>(u);
    else
      root = std::make_unique<SetLeaf>(u);
  }

  size_t Set::size() const {
    return sz;
  }

  bool Set::member(key_bit_t x) const {
    return root->member(x);
  }

  key_bit_t Set::successor(key_bit_t x) const {
    return root->successor(x);
  }

  key_bit_t Set::predecessor(key_bit_t x) const {
    return root->predecessor(x);
  }

  key_bit_t Set::minimum() const {
    return root->minimum();
  }

  key_bit_t Set::maximum() const {
    return root->maximum();
  }

  bool Set::insert(key_bit_t x){
    return root->insert(x) ? (++sz, true) : false;
  }

  bool Set::remove(key_bit_t x){
    return root->remove(x) ? (--sz, true) : false;
  }

  key_bit_t Set::extract_min(){
    key_bit_t x = root->extract_min();
    if(x != NIL_KEY_BIT) --sz;
    return x;
  }

}