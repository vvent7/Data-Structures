#include <cstddef>
#include "veb_base/_veb.h"
#include "veb_base/veb_inner.h"
#include "veb_base/veb_leaf.h"
#include "veb_base/veb.h"
#include "utils.h"

// =============Veb===============
Veb::Veb():
  root(nullptr), sz(0){}

Veb::Veb(int u){
  root = (u > _veb::BASE_U)
    ? static_cast<_veb*> (new VebInner(u))
    : static_cast<_veb*> (new VebLeaf(u));
}

size_t Veb::size(){
  return sz;
}

bool Veb::insert(int x){
  return root->insert(x) ? (sz++, true) : false;
}

bool Veb::remove(int x){
  return root->remove(x) ? (sz--, true) : false;
}

bool Veb::member(int x){
  return root->member(x);
}

int Veb::successor(int x){
  return root->successor(x);
}

int Veb::predecessor(int x){
  return root->predecessor(x);
}

int Veb::minimum(){
  return root->minimum();
}

int Veb::maximum(){
  return root->maximum();
}

int Veb::extract_min(){
  int x = root->extract_min();
  if(x != _veb::NIL) sz--;
  return x;
}
// =================================