#include <cstddef>
#include <memory>
#include "veb/_veb_node.h"
#include "veb/veb_inner.h"
#include "veb/veb_leaf.h"
#include "veb/veb.h"
#include "utils.h"

// =============Veb===============
Veb::Veb():
  root(nullptr), sz(0){}

Veb::Veb(int u){
  if(u > _veb_node::BASE_U)
    root = std::make_unique<VebInner>(u);
  else
    root = std::make_unique<VebLeaf>(u);
}

size_t Veb::size() const {
  return sz;
}

bool Veb::member(int x) const {
  return root->member(x);
}

int Veb::successor(int x) const {
  return root->successor(x);
}

int Veb::predecessor(int x) const {
  return root->predecessor(x);
}

int Veb::minimum() const {
  return root->minimum();
}

int Veb::maximum() const {
  return root->maximum();
}

bool Veb::insert(int x){
  return root->insert(x) ? (sz++, true) : false;
}

bool Veb::remove(int x){
  return root->remove(x) ? (sz--, true) : false;
}

int Veb::extract_min(){
  int x = root->extract_min();
  if(x != _veb_node::NIL) sz--;
  return x;
}
// =================================