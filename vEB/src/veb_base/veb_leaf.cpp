#include "veb/_veb_node.h"
#include "veb/veb_leaf.h"

// ==========VebLeaf==========
VebLeaf::VebLeaf():
  u(0), values(0){}

VebLeaf::VebLeaf(int u):
  u(u), values(0){ }

int VebLeaf::minimum() const {
  if(values == 0) return _veb_node::NIL;
  return __builtin_ffsll(values)-1;
}

int VebLeaf::maximum() const {
  if(values == 0) return _veb_node::NIL;
  return _veb_node::BASE_U - 1 - __builtin_clzll(values);
}

bool VebLeaf::member(int x) const {
  if(x >= u) return false;
  return (values & (1ULL << x)) != 0;
}

int VebLeaf::successor(int x) const {
  if(x >= u-1) return _veb_node::NIL;
  unsigned long long mask = ~((1ULL << (x+1)) - 1);
  unsigned long long succ = values & mask;

  int ans = __builtin_ffsll(succ);

  return ans > 0 ? ans-1 : _veb_node::NIL;
}

int VebLeaf::predecessor(int x) const {
  if(x >= u) return _veb_node::NIL;
  unsigned long long mask = (1ULL << x) - 1;
  unsigned long long pred = values & mask;

  if(pred == 0) return _veb_node::NIL;

  int ans = __builtin_clzll(pred);
  
  return _veb_node::BASE_U - 1 - ans;
}

bool VebLeaf::insert(int x){
  if(member(x)) return false;
  values |= (1ULL << x);
  return true;
}

bool VebLeaf::remove(int x){
  if(!member(x)) return false;
  values &= ~(1ULL << x);
  return true;
}

int VebLeaf::extract_min(){
  int x = minimum();
  if(x != _veb_node::NIL) remove(x);
  return x;
}
// =================================