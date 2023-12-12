#include <climits> //MAX
#include <memory> //unique_ptr
#include <climits> //MAX
#include "veb_multi/_veb_multi_node.h"
#include "veb_multi/veb_multi.h"
#include "veb_multi/veb_multi_inner.h"
#include "veb_multi/veb_multi_leaf.h"
#include "utils.h"

VebMulti::VebMulti():root(nullptr){}

VebMulti::VebMulti(int u){
  if(u > _veb_multi_node::BASE_U)
    root = std::make_unique<VebMultiInner>(u);
  else
    root = std::make_unique<VebMultiLeaf>(u);
}

bool VebMulti::empty() const {
  return root->empty();
}

int VebMulti::minimum(unsigned long long *cnt) const {
  return root->minimum(cnt);
}

int VebMulti::maximum(unsigned long long *cnt) const {
  return root->maximum(cnt);
}

int VebMulti::member(int x) const {
  return root->member(x);
}

int VebMulti::successor(int x, unsigned long long *cnt) const{
  return root->successor(x, cnt);
}

int VebMulti::predecessor(int x, unsigned long long *cnt) const{
  return root->predecessor(x, cnt);
}

unsigned long long VebMulti::insert(int x, unsigned long long n, unsigned long long *cnt){
  return n==0
    ? deal_opt(cnt, 0), 0
    : root->insert(x, n, cnt);
}

unsigned long long VebMulti::remove(int x, unsigned long long n, unsigned long long *cnt){
  return n==0
    ? deal_opt(cnt, 0), 0
    : root->remove(x, n, cnt);
}

int VebMulti::extract_min(unsigned long long *cnt){
  return root->extract_min(cnt);
}