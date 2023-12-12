#include <algorithm>
#include <memory>
#include "veb_multi/_veb_multi_node.h"
#include "veb_multi/veb_multi_leaf.h"
#include "utils.h"

// ==========VebMultiLeaf==========
VebMultiLeaf::VebMultiLeaf():
  u(0), values(0), cntValues(nullptr){}

VebMultiLeaf::VebMultiLeaf(int u):
  u(u), values(0),
  cntValues(std::make_unique<unsigned long long[]>(u)){ }

inline bool VebMultiLeaf::empty() const {
  return values == 0;
}

int VebMultiLeaf::minimum(unsigned long long *cnt) const {
  if(empty()) return deal_opt(cnt, 0), _veb_multi_node::NIL;

  int x = __builtin_ffsll(values)-1;
  
  return deal_opt(cnt, cntValues[x]), x;
}

int VebMultiLeaf::maximum(unsigned long long *cnt) const {
  if(empty()) return deal_opt(cnt, 0), _veb_multi_node::NIL;

  int x = _veb_multi_node::BASE_U - 1 - __builtin_clzll(values);
  
  return deal_opt(cnt, cntValues[x]), x;
}

int VebMultiLeaf::member(int x) const {
  if(x >= u) return 0;
  return cntValues[x];
}

int VebMultiLeaf::successor(int x, unsigned long long *cnt) const {
  if(x >= u-1) return deal_opt(cnt, 0), _veb_multi_node::NIL;
  unsigned long long mask = ~((1ULL << (x+1)) - 1);
  unsigned long long succ = values & mask;

  int ans = __builtin_ffsll(succ);

  return ans <= 0
    ? (deal_opt(cnt, 0),  _veb_multi_node::NIL)
    : (deal_opt(cnt, cntValues[ans-1]), ans-1);
}

int VebMultiLeaf::predecessor(int x, unsigned long long *cnt) const {
  if(x >= u) return deal_opt(cnt, 0), _veb_multi_node::NIL;
  unsigned long long mask = (1ULL << x) - 1;
  unsigned long long pred = values & mask;

  if(pred == 0) return deal_opt(cnt, 0), _veb_multi_node::NIL;

  int ans = __builtin_clzll(pred);
  int predX = _veb_multi_node::BASE_U - 1 - ans;
  return deal_opt(cnt, cntValues[predX]), predX;
}

unsigned long long VebMultiLeaf::insert(int x, unsigned long long n, unsigned long long *cnt){
  if((x>=u) | (n<=0)) return deal_opt(cnt, 0), 0;
  
  values |= (1ULL << x);
  n = std::min(n, ULLONG_MAX - cntValues[x]);
  cntValues[x] += n;

  return deal_opt(cnt, cntValues[x]), n;
}

unsigned long long VebMultiLeaf::remove(int x, unsigned long long n, unsigned long long *cnt){
  if((x>=u) | (n<=0)) return deal_opt(cnt, 0), 0;
  
  n = std::min(n, cntValues[x]);
  cntValues[x] -= n;
  if(cntValues[x] == 0) values &= ~(1ULL << x);
  
  return deal_opt(cnt, cntValues[x]), n;
}

int VebMultiLeaf::extract_min(unsigned long long *cnt){
  if(empty()) return deal_opt(cnt, 0), _veb_multi_node::NIL;
  int x = minimum();
  return remove(x, 1, cnt), x;
}
// =================================