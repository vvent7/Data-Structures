#include <algorithm>
#include "_veb_multi.h"
#include "veb_multi_leaf.h"

// ==========VebMultiLeaf==========
VebMultiLeaf::VebMultiLeaf():
  u(0), values(0), cntValues(nullptr){}

VebMultiLeaf::VebMultiLeaf(int u):
  u(u), values(0), cntValues(new int[u]){ }

VebMultiLeaf::~VebMultiLeaf(){
  delete[] cntValues;
}

int VebMultiLeaf::minimum(int *cnt = nullptr) const {
  if(values == 0) return _veb_multi::NIL;

  int x = __builtin_ffsll(values)-1;
  if(cnt != nullptr) *cnt = cntValues[x];

  return x;
}

int VebMultiLeaf::maximum(int *cnt = nullptr) const {
  if(values == 0) return _veb_multi::NIL;

  int x = _veb_multi::BASE_U - 1 - __builtin_clzll(values);
  if(cnt != nullptr) *cnt = cntValues[x];

  return x;
}

int VebMultiLeaf::member(int x) const {
  if(x >= u) return 0;
  return cntValues[x];
}

int VebMultiLeaf::successor(int x, int *cnt = nullptr) const {
  if(x >= u-1) return _veb_multi::NIL;
  unsigned long long mask = ~((1ULL << (x+1)) - 1);
  unsigned long long succ = values & mask;

  int ans = __builtin_ffsll(succ);
  if(ans<=0) return _veb_multi::NIL;
  if(cnt != nullptr) *cnt = cntValues[ans-1];

  return ans-1;
}

int VebMultiLeaf::predecessor(int x, int *cnt = nullptr) const {
  if(x >= u) return _veb_multi::NIL;
  unsigned long long mask = (1ULL << x) - 1;
  unsigned long long pred = values & mask;

  if(pred == 0) return _veb_multi::NIL;

  int ans = __builtin_clzll(pred);
  int x = _veb_multi::BASE_U - 1 - ans;
  if(cnt != nullptr) *cnt = cntValues[x];
  
  return x;
}

int VebMultiLeaf::insert(int x, int n = 1, int *cnt = nullptr){
  if(x>=u || n<=0) return 0;
  
  values |= (1ULL << x);
  n = std::min(n, INT_MAX - cntValues[x]);
  cntValues[x] += n;

  if(cnt != nullptr) *cnt = cntValues[x];

  return n;
}

int VebMultiLeaf::remove(int x, int n = INT_MAX, int *cnt = nullptr){
  if(x>=u || n<=0) return 0;
  
  n = std::min(n, cntValues[x]);
  cntValues[x] -= n;
  if(cntValues[x] == 0) values &= ~(1ULL << x);
  
  if(cnt != nullptr) *cnt = cntValues[x];

  return n;
}

int VebMultiLeaf::extract_min(int *cnt = nullptr){
  int x = minimum();
  if(x != _veb_multi::NIL) remove(x, 1, cnt);
  return x;
}
// =================================