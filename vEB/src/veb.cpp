#include <iostream>
#include <memory>
#include <climits>
#include <cstddef>
#include "veb.h"
#include "_veb_base.h"
#include "utils.h"

// ==========VebNodeInner==========
VebNodeInner::VebNodeInner():
  k(0), u(0), uSqrtUpper(0), uSqrtLower(0),
  mi(Veb::NIL), mx(Veb::NIL),
  summary(nullptr), clusters(nullptr){}

VebNodeInner::VebNodeInner(int u):
  k(first_power_of_2(u)),
  u(1<<k),
  uSqrtUpper(upper_sqrt(u)),
  uSqrtLower(lower_sqrt(u)),
  mi(Veb::NIL), mx(Veb::NIL){

  if(u <= Veb::BASE_U) return; // base case(shouldn't reach)

  summary = (uSqrtUpper > Veb::BASE_U)
    ? static_cast<VebNode*> (new VebNodeInner(uSqrtUpper))
    : static_cast<VebNode*> (new VebNodeLeaf(uSqrtUpper));

  clusters = new VebNode*[uSqrtUpper];
  if(uSqrtLower > Veb::BASE_U){
    for(int i=0; i<uSqrtUpper; i++)
      clusters[i] = new VebNodeInner(uSqrtLower);
  }
  else{
    for(int i=0;i<uSqrtUpper; i++)
      clusters[i] = new VebNodeLeaf(uSqrtLower);
  }
}

VebNodeInner::~VebNodeInner(){
  if(summary!=nullptr) delete summary;
  if(clusters!=nullptr) delete[] clusters;
}

bool VebNodeInner::insert(int x){
  if(mi == Veb::NIL) // empty set
    return (mi = mx = x), true;

  if(x==mi) return false; // already inserted

  bool inserted = false;
  if(x < mi){ // update minimum
    std::swap(x, mi);
    inserted = true;
  }

  if(u > Veb::BASE_U){ // not a base case
    int i = high(x), j = low(x);
    if(clusters[i]->minimum() == Veb::NIL)
      summary->insert(i);
    inserted = clusters[i]->insert(j);
  }
  if(x > mx) mx = x, inserted = true;
  return inserted;
}

bool VebNodeInner::remove(int x){
  if(mi == Veb::NIL) return false; // empty set
  else if(mi == mx) // only one element
    return x != mi ? false : (mi = mx = Veb::NIL, true);
  else if(u <= 2){ // base case (2 elements exists)
    if(x == 0) return mi = 1, true;
    else if(x == 1) return mx = 0, true;
    return false;
  }
  else if(x == mi){ // update minimum
    int firstCluster = summary->minimum();
    x = mi = index(firstCluster, clusters[firstCluster]->minimum());
  }

  int i = high(x), j = low(x);
  bool removed = clusters[i]->remove(j);

  if(!removed) return false;

  // update summary (clusters[i] emptied)
  if(clusters[i]->minimum() == Veb::NIL){
    summary->remove(i);
    if(x == mx){ // update maximum (x was the maximum)
      int summaryMax = summary->maximum();
      if(summaryMax == Veb::NIL) mx = mi;
      else mx = index(summaryMax, clusters[summaryMax]->maximum());
    }
  }
  else if(x == mx) // update maximum (x was the maximum)
    mx = index(i, clusters[i]->maximum());

  return true;
}

bool VebNodeInner::member(int x){
  if(x == mi || x == mx) return true;
  else if(u <= 2) return false;
  else{
    return clusters[high(x)]->member(low(x));
  }
}

int VebNodeInner::successor(int x){
  if(u<=2){
    if(x == 0 && mx == 1) return 1;
    else return Veb::NIL;
  }
  else if(mi != Veb::NIL && x < mi) return mi;
  else{
    int i = high(x), j = low(x);
    int maxLow = clusters[i]->maximum();

    if(maxLow != Veb::NIL && j < maxLow){
      int offset = clusters[i]->successor(j);
      return index(i, offset);
    }
    else{
      int succCluster = summary->successor(i);
      if(succCluster == Veb::NIL) return Veb::NIL;
      else{
        int offset = clusters[succCluster]->minimum();
        return index(succCluster, offset);
      }
    }
  }
}

int VebNodeInner::predecessor(int x){
  if(u<=2){
    if(x == 1 && mi == 0) return 0;
    else return Veb::NIL;
  }
  else if(mx != Veb::NIL && x > mx) return mx;
  else{
    int i = high(x), j = low(x);
    int minLow = clusters[i]->minimum();

    if(minLow != Veb::NIL && j > minLow){
      int offset = clusters[i]->predecessor(j);
      return index(i, offset);
    }
    else{
      int predCluster = summary->predecessor(i);
      if(predCluster == Veb::NIL)
        return (mi != Veb::NIL && x > mi) ? mi : Veb::NIL;
      else{
        int offset = clusters[predCluster]->maximum();
        return index(predCluster, offset);
      }
    }
  }
}

int VebNodeInner::minimum(){
  return mi;
}

int VebNodeInner::maximum(){
  return mx;
}

int VebNodeInner::extract_min(){
  int x = mi;
  if(x != Veb::NIL) remove(x);
  return x;
}

//PRIVATE
inline int VebNodeInner::high(int x){
  return x/uSqrtLower;
}
inline int VebNodeInner::low(int x){
  return x%uSqrtLower;
}
inline int VebNodeInner::index(int x, int y){
  return x*uSqrtLower + y;
}


// ==========VebNodeLeaf==========
VebNodeLeaf::VebNodeLeaf():
  u(0), values(0){}

VebNodeLeaf::VebNodeLeaf(int u):
  u(u), values(0){ }

bool VebNodeLeaf::insert(int x){
  if(member(x)) return false;
  values |= (1ULL << x);
  return true;
}

bool VebNodeLeaf::remove(int x){
  if(!member(x)) return false;
  values &= ~(1ULL << x);
  return true;
}

bool VebNodeLeaf::member(int x){
  if(x >= u) return false;
  return (values & (1ULL << x)) != 0;
}

int VebNodeLeaf::successor(int x){
  if(x >= u-1) return Veb::NIL;
  unsigned long long mask = ~((1ULL << (x+1)) - 1);
  unsigned long long succ = values & mask;

  int ans = __builtin_ffsll(succ);

  return ans > 0 ? ans-1 : Veb::NIL;
}

int VebNodeLeaf::predecessor(int x){
  if(x >= u) return Veb::NIL;
  unsigned long long mask = (1ULL << x) - 1;
  unsigned long long pred = values & mask;

  if(pred == 0) return Veb::NIL;

  int ans = __builtin_clzll(pred);
  
  return Veb::BASE_U-1-ans;
}

int VebNodeLeaf::minimum(){
  if(values == 0) return Veb::NIL;
  return __builtin_ffsll(values)-1;
}

int VebNodeLeaf::maximum(){
  if(values == 0) return Veb::NIL;
  return Veb::BASE_U-1-__builtin_clzll(values);
}

int VebNodeLeaf::extract_min(){
  int x = minimum();
  if(x != Veb::NIL) remove(x);
  return x;
}
// =================================

// =============Veb===============
Veb::Veb():
  root(nullptr), sz(0){}

Veb::Veb(int u){
  root = (u > Veb::BASE_U)
    ? static_cast<VebNode*> (new VebNodeInner(u))
    : static_cast<VebNode*> (new VebNodeLeaf(u));
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
  if(x != Veb::NIL) sz--;
  return x;
}
// =================================