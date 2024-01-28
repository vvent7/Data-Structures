#include <algorithm>
#include "utils.h"
#include "veb/veb_env.h"
#include "veb/veb_set/_veb_set_node.h"
#include "veb/veb_set/veb_set_inner.h"
#include "veb/veb_set/veb_set_leaf.h"


namespace veb{

  SetInner::SetInner():
    k(0), u(0), uSqrtUpper(0), uSqrtLower(0),
    mi(NIL_KEY_BIT), mx(NIL_KEY_BIT),
    summary(nullptr), clusters(nullptr){}

  SetInner::SetInner(key_bit_t u):
    k(utils::lower_bound_pow2(u)),
    u(1ULL<<k),
    uSqrtUpper(upper_sqrt(u)),
    uSqrtLower(lower_sqrt(u)),
    mi(NIL_KEY_BIT), mx(NIL_KEY_BIT){

    if(u <= 2) return; //leaf 2

    summary = (uSqrtUpper > BASE_U)
      ? static_cast<_set_node*> (new SetInner(uSqrtUpper))
      : static_cast<_set_node*> (new SetLeaf(uSqrtUpper));

    clusters = new _set_node*[uSqrtUpper];
    if(uSqrtLower > BASE_U){
      for(key_bit_t i=0; i<uSqrtUpper; ++i)
        clusters[i] = new SetInner(uSqrtLower);
    }
    else{
      for(key_bit_t i=0;i<uSqrtUpper; ++i)
        clusters[i] = new SetLeaf(uSqrtLower);
    }
  }

  SetInner::~SetInner(){
    if(summary!=nullptr) delete summary;
    if(clusters!=nullptr){
      for(key_bit_t i=0;i<uSqrtUpper; ++i)
        delete clusters[i];
      delete[] clusters;
    }
  }

  bool SetInner::empty() const {
    return mi == NIL_KEY_BIT;
  }

  key_bit_t SetInner::minimum() const {
    return mi;
  }

  key_bit_t SetInner::maximum() const {
    return mx;
  }

  bool SetInner::member(key_bit_t x) const {
    if(x == mi || x == mx) return true;
    else if(u <= 2) return false;
    else{
      return clusters[high(x, uSqrtLower)]->member(low(x, uSqrtLower));
    }
  }

  key_bit_t SetInner::successor(key_bit_t x) const {
    if(u<=2){
      if(x == 0 && mx == 1) return 1;
      else return NIL_KEY_BIT;
    }
    else if(mi != NIL_KEY_BIT && x < mi) return mi;
    else{
      key_bit_t i = high(x, uSqrtLower), j = low(x, uSqrtLower);
      key_bit_t maxLow = clusters[i]->maximum();

      if(maxLow != NIL_KEY_BIT && j < maxLow){
        key_bit_t offset = clusters[i]->successor(j);
        return index(i, offset, uSqrtLower);
      }
      else{
        key_bit_t succCluster = summary->successor(i);
        if(succCluster == NIL_KEY_BIT) return NIL_KEY_BIT;
        else{
          key_bit_t offset = clusters[succCluster]->minimum();
          return index(succCluster, offset, uSqrtLower);
        }
      }
    }
  }

  key_bit_t SetInner::predecessor(key_bit_t x) const {
    if(u<=2){
      if(x == 1 && mi == 0) return 0;
      else return NIL_KEY_BIT;
    }
    else if(mx != NIL_KEY_BIT && x > mx) return mx;
    else{
      key_bit_t i = high(x, uSqrtLower), j = low(x, uSqrtLower);
      key_bit_t minLow = clusters[i]->minimum();

      if(minLow != NIL_KEY_BIT && j > minLow){
        key_bit_t offset = clusters[i]->predecessor(j);
        return index(i, offset, uSqrtLower);
      }
      else{
        key_bit_t predCluster = summary->predecessor(i);
        if(predCluster == NIL_KEY_BIT)
          return (mi != NIL_KEY_BIT && x > mi) ? mi : NIL_KEY_BIT;
        else{
          key_bit_t offset = clusters[predCluster]->maximum();
          return index(predCluster, offset, uSqrtLower);
        }
      }
    }
  }

  bool SetInner::insert(key_bit_t x){
    if(mi == NIL_KEY_BIT) // empty set
      return (mi = mx = x), true;

    if(x==mi) return false; // already inserted

    bool inserted = false;
    if(x < mi){ // update minimum
      std::swap(x, mi);
      inserted = true;
    }

    if(u > BASE_U){ // not a base case
      key_bit_t i = high(x, uSqrtLower), j = low(x, uSqrtLower);
      if(clusters[i]->minimum() == NIL_KEY_BIT)
        summary->insert(i);
      inserted = clusters[i]->insert(j);
    }
    if(x > mx) mx = x, inserted = true;
    return inserted;
  }

  bool SetInner::remove(key_bit_t x){
    if(mi == NIL_KEY_BIT) return false; // empty set
    else if(mi == mx) // only one element
      return x != mi ? false : (mi = mx = NIL_KEY_BIT, true);
    else if(u <= 2){ // base case (2 elements exists)
      if(x == 0) return mi = 1, true;
      else if(x == 1) return mx = 0, true;
      return false;
    }
    else if(x == mi){ // update minimum
      key_bit_t firstCluster = summary->minimum();
      x = mi = index(firstCluster, clusters[firstCluster]->minimum(), uSqrtLower);
    }

    key_bit_t i = high(x, uSqrtLower), j = low(x, uSqrtLower);
    bool removed = clusters[i]->remove(j);

    if(!removed) return false;

    // update summary (clusters[i] emptied)
    if(clusters[i]->minimum() == NIL_KEY_BIT){
      summary->remove(i);
      if(x == mx){ // update maximum (x was the maximum)
        key_bit_t summaryMax = summary->maximum();
        if(summaryMax == NIL_KEY_BIT) mx = mi;
        else mx = index(summaryMax, clusters[summaryMax]->maximum(), uSqrtLower);
      }
    }
    else if(x == mx) // update maximum (x was the maximum)
      mx = index(i, clusters[i]->maximum(), uSqrtLower);

    return true;
  }

  key_bit_t SetInner::extract_min(){
    key_bit_t x = mi;
    if(x != NIL_KEY_BIT) remove(x);
    return x;
  }

}