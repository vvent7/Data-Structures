#include <climits> //ULLONG_MAX
#include <memory> //unique_ptr
#include "utils.h"
#include "veb/veb_env.h" //key_bit_t
#include "veb/veb_multi/_veb_multi_node.h"
#include "veb/veb_multi/veb_multi_inner.h"
#include "veb/veb_multi/veb_multi_leaf.h"
#include "veb/veb_multi/veb_multi.h"

namespace veb {

  Multi::Multi():root(nullptr){}

  Multi::Multi(key_bit_t u){
    if(u > BASE_U)
      root = std::make_unique<MultiInner>(u);
    else
      root = std::make_unique<MultiLeaf>(u);
  }

  bool Multi::empty() const {
    return root->empty();
  }

  key_bit_t Multi::minimum(unsigned long long *cnt) const {
    return root->minimum(cnt);
  }

  key_bit_t Multi::maximum(unsigned long long *cnt) const {
    return root->maximum(cnt);
  }

  unsigned long long Multi::member(key_bit_t x) const {
    return root->member(x);
  }

  key_bit_t Multi::successor(key_bit_t x, unsigned long long *cnt) const{
    return root->successor(x, cnt);
  }

  key_bit_t Multi::predecessor(key_bit_t x, unsigned long long *cnt) const{
    return root->predecessor(x, cnt);
  }

  unsigned long long Multi::insert(key_bit_t x, unsigned long long n, unsigned long long *cnt){
    return n==0
      ? deal_opt(cnt, 0), 0
      : root->insert(x, n, cnt);
  }

  unsigned long long Multi::remove(key_bit_t x, unsigned long long n, unsigned long long *cnt){
    return n==0
      ? deal_opt(cnt, 0), 0
      : root->remove(x, n, cnt);
  }

  key_bit_t Multi::extract_min(unsigned long long *cnt){
    return root->extract_min(cnt);
  }

}