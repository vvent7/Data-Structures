#include <algorithm>
#include "veb/_veb_node.h"
#include "veb/veb_inner.h"
#include "veb/veb_leaf.h"
#include "utils.h"

// ==========VebInner==========
VebInner::VebInner():
  k(0), u(0), uSqrtUpper(0), uSqrtLower(0),
  mi(_veb_node::NIL), mx(_veb_node::NIL),
  summary(nullptr), clusters(nullptr){}

VebInner::VebInner(int u):
  k(first_power_of_2(u)),
  u(1<<k),
  uSqrtUpper(upper_sqrt(u)),
  uSqrtLower(lower_sqrt(u)),
  mi(_veb_node::NIL), mx(_veb_node::NIL){

  if(u <= _veb_node::BASE_U) return; // base case(shouldn't reach)

  summary = (uSqrtUpper > _veb_node::BASE_U)
    ? static_cast<_veb_node*> (new VebInner(uSqrtUpper))
    : static_cast<_veb_node*> (new VebLeaf(uSqrtUpper));

  clusters = new _veb_node*[uSqrtUpper];
  if(uSqrtLower > _veb_node::BASE_U){
    for(int i=0; i<uSqrtUpper; i++)
      clusters[i] = new VebInner(uSqrtLower);
  }
  else{
    for(int i=0;i<uSqrtUpper; i++)
      clusters[i] = new VebLeaf(uSqrtLower);
  }
}

VebInner::~VebInner(){
  if(summary!=nullptr) delete summary;
  if(clusters!=nullptr){
    for(int i=0;i<uSqrtUpper;i++)
      delete clusters[i];
    delete[] clusters;
  }
}

int VebInner::minimum() const {
  return mi;
}

int VebInner::maximum() const {
  return mx;
}

bool VebInner::member(int x) const {
  if(x == mi || x == mx) return true;
  else if(u <= 2) return false;
  else{
    return clusters[high(x, uSqrtLower)]->member(low(x, uSqrtLower));
  }
}

int VebInner::successor(int x) const {
  if(u<=2){
    if(x == 0 && mx == 1) return 1;
    else return _veb_node::NIL;
  }
  else if(mi != _veb_node::NIL && x < mi) return mi;
  else{
    int i = high(x, uSqrtLower), j = low(x, uSqrtLower);
    int maxLow = clusters[i]->maximum();

    if(maxLow != _veb_node::NIL && j < maxLow){
      int offset = clusters[i]->successor(j);
      return index(i, offset, uSqrtLower);
    }
    else{
      int succCluster = summary->successor(i);
      if(succCluster == _veb_node::NIL) return _veb_node::NIL;
      else{
        int offset = clusters[succCluster]->minimum();
        return index(succCluster, offset, uSqrtLower);
      }
    }
  }
}

int VebInner::predecessor(int x) const {
  if(u<=2){
    if(x == 1 && mi == 0) return 0;
    else return _veb_node::NIL;
  }
  else if(mx != _veb_node::NIL && x > mx) return mx;
  else{
    int i = high(x, uSqrtLower), j = low(x, uSqrtLower);
    int minLow = clusters[i]->minimum();

    if(minLow != _veb_node::NIL && j > minLow){
      int offset = clusters[i]->predecessor(j);
      return index(i, offset, uSqrtLower);
    }
    else{
      int predCluster = summary->predecessor(i);
      if(predCluster == _veb_node::NIL)
        return (mi != _veb_node::NIL && x > mi) ? mi : _veb_node::NIL;
      else{
        int offset = clusters[predCluster]->maximum();
        return index(predCluster, offset, uSqrtLower);
      }
    }
  }
}

bool VebInner::insert(int x){
  if(mi == _veb_node::NIL) // empty set
    return (mi = mx = x), true;

  if(x==mi) return false; // already inserted

  bool inserted = false;
  if(x < mi){ // update minimum
    std::swap(x, mi);
    inserted = true;
  }

  if(u > _veb_node::BASE_U){ // not a base case
    int i = high(x, uSqrtLower), j = low(x, uSqrtLower);
    if(clusters[i]->minimum() == _veb_node::NIL)
      summary->insert(i);
    inserted = clusters[i]->insert(j);
  }
  if(x > mx) mx = x, inserted = true;
  return inserted;
}

bool VebInner::remove(int x){
  if(mi == _veb_node::NIL) return false; // empty set
  else if(mi == mx) // only one element
    return x != mi ? false : (mi = mx = _veb_node::NIL, true);
  else if(u <= 2){ // base case (2 elements exists)
    if(x == 0) return mi = 1, true;
    else if(x == 1) return mx = 0, true;
    return false;
  }
  else if(x == mi){ // update minimum
    int firstCluster = summary->minimum();
    x = mi = index(firstCluster, clusters[firstCluster]->minimum(), uSqrtLower);
  }

  int i = high(x, uSqrtLower), j = low(x, uSqrtLower);
  bool removed = clusters[i]->remove(j);

  if(!removed) return false;

  // update summary (clusters[i] emptied)
  if(clusters[i]->minimum() == _veb_node::NIL){
    summary->remove(i);
    if(x == mx){ // update maximum (x was the maximum)
      int summaryMax = summary->maximum();
      if(summaryMax == _veb_node::NIL) mx = mi;
      else mx = index(summaryMax, clusters[summaryMax]->maximum(), uSqrtLower);
    }
  }
  else if(x == mx) // update maximum (x was the maximum)
    mx = index(i, clusters[i]->maximum(), uSqrtLower);

  return true;
}

int VebInner::extract_min(){
  int x = mi;
  if(x != _veb_node::NIL) remove(x);
  return x;
}