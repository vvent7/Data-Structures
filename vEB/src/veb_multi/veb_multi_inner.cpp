#include <algorithm>
#include <memory>
#include "veb_multi/veb_multi_inner.h"
#include "veb_multi/veb_multi_leaf.h"
#include "utils.h"

// ==========VebMultiInner==========
VebMultiInner::VebMultiInner():
  k(0), u(0), uSqrtUpper(0), uSqrtLower(0),
  mi(_veb_multi::NIL), mx(_veb_multi::NIL),
  cntMi(0), cntMx(0),
  summary(nullptr), clusters(nullptr){}

VebMultiInner::VebMultiInner(int u):
  k(first_power_of_2(u)),
  u(1<<k),
  uSqrtUpper(upper_sqrt(u)),
  uSqrtLower(lower_sqrt(u)),
  mi(_veb_multi::NIL), mx(_veb_multi::NIL),
  cntMi(0), cntMx(0){

  if(u <= 2) return; //leaf 2

  clusters = std::make_unique<std::unique_ptr<_veb_multi>[]>(uSqrtUpper);

  if(uSqrtUpper > _veb_multi::BASE_U)
    summary = std::make_unique<VebMultiInner>(uSqrtUpper);
  else
    summary = std::make_unique<VebMultiLeaf>(uSqrtUpper);

  if(uSqrtLower > _veb_multi::BASE_U){
    for(int i=0; i<uSqrtUpper; i++)
      clusters[i] = std::make_unique<VebMultiInner>(uSqrtLower);
  }
  else{
    for(int i=0;i<uSqrtUpper; i++)
      clusters[i] = std::make_unique<VebMultiLeaf>(uSqrtLower);
  }
}

inline bool VebMultiInner::empty() const {
  return mi == _veb_multi::NIL;
}

int VebMultiInner::minimum(unsigned long long *cnt = nullptr) const {
  return deal_opt(cnt, cntMi), mi;
}

int VebMultiInner::maximum(unsigned long long *cnt = nullptr) const {
  return deal_opt(cnt, cntMx), mx;
}

int VebMultiInner::member(int x) const {
  if(x == mi) return cntMi;
  else if(x == mx) return cntMx;
  else if(u <= 2) return 0;
  else return clusters[high(x, uSqrtLower)]->member(low(x, uSqrtLower));
}

int VebMultiInner::successor(int x, unsigned long long *cnt = nullptr) const {
  if(u<=2){
    return (x == 0 && mx == 1)
      ? (deal_opt(cnt, cntMx), mx)
      : (deal_opt(cnt, 0), _veb_multi::NIL);
  }
  else if(!empty() && x < mi)
    return deal_opt(cnt, cntMi), mi;
  else{
    int i = high(x, uSqrtLower), j = low(x, uSqrtLower);
    if(!clusters[i]->empty() && j < clusters[i]->maximum()){
      // successor is in the same cluster
      int offset = clusters[i]->successor(j, cnt);
      return index(i, offset, uSqrtLower);
    }
    else{
      // successor is in the next cluster
      int succCluster = summary->successor(i);

      if(succCluster == _veb_multi::NIL){
        return (!empty() && x < mx)
          ? (deal_opt(cnt, cntMx), mx)
          : (deal_opt(cnt, 0), _veb_multi::NIL);
      }
      else{
        int offset = clusters[succCluster]->minimum();
        return index(succCluster, offset, uSqrtLower);
      }
    }
  }
}

int VebMultiInner::predecessor(int x, unsigned long long *cnt = nullptr) const {
  if(u<=2){
    return (x == 1 && mi == 0)
      ? (deal_opt(cnt, cntMi), mi)
      : (deal_opt(cnt, 0), _veb_multi::NIL);
  }
  else if(!empty() && x > mx)
    return deal_opt(cnt, cntMx), mx;
  else{
    int i = high(x, uSqrtLower), j = low(x, uSqrtLower);
    if(!clusters[i]->empty() && j > clusters[i]->minimum()){
      // predecessor is in the same cluster
      int offset = clusters[i]->predecessor(j, cnt);
      return index(i, offset, uSqrtLower);
    }
    else{
      // predecessor is in the previous cluster
      int predCluster = summary->predecessor(i);

      if(predCluster == _veb_multi::NIL){
        return (!empty() && x > mi)
          ? (deal_opt(cnt, cntMi), mi)
          : (deal_opt(cnt, 0), _veb_multi::NIL);
      }
      else{
        int offset = clusters[predCluster]->maximum();
        return index(predCluster, offset, uSqrtLower);
      }
    }
  }
}

unsigned long long VebMultiInner::insert(int x, unsigned long long n = 1, unsigned long long *cnt = nullptr){
  if(empty())
    return (mi = mx = x), (cntMi = cntMx = n),
      deal_opt(cnt,n), n;

  if(x == mi){
    n = std::min(n, ULLONG_MAX - cntMi);
    cntMi += n;
    if(x == mx) cntMx = cntMi;
    return deal_opt(cnt, cntMi), n;
  }
  else if(x == mx){
    n = std::min(n, ULLONG_MAX - cntMx);
    cntMx += n;
    return deal_opt(cnt, cntMx), n;
  } //x!=mi && x!=mx
  else if(mi == mx){ // only one element
    if(x < mi) mi = x, cntMi = n;
    else mx = x, cntMx = n;
    return deal_opt(cnt, n), n;
  }

  char swapped = 0;
  if(x < mi){ // update minimum (1)
    deal_opt(cnt, n), swapped = 1;
    std::swap(x, mi);
    std::swap(n, cntMi);
  }
  else if(x > mx){ // update maximum (2)
    deal_opt(cnt, n), swapped = 2;
    std::swap(x, mx);
    std::swap(n, cntMx);
  }

  int i = high(x, uSqrtLower), j = low(x, uSqrtLower);
  if(clusters[i]->empty())
    summary->insert(i);
  
  return swapped == 0
    ? clusters[i]->insert(j, n, cnt) // not swapped
    : (clusters[i]->insert(j, n), (swapped == 1 ? cntMi : cntMx)); // swapped
}

unsigned long long VebMultiInner::remove(int x, unsigned long long n = ULLONG_MAX, unsigned long long *cnt = nullptr){
  if(empty() | (x < mi) | (x > mx)) return deal_opt(cnt, 0), 0;
  else if(mi == mx){ // only one element
    if(x != mi) return deal_opt(cnt, 0), 0;
    cntMi -= (n = std::min(n, cntMi));
    if(cntMi == 0) mi = _veb_multi::NIL;
    mx = mi; cntMx = cntMi;
    return deal_opt(cnt, cntMi), n;
  }
  else if(x == mi){ // update minimum
    cntMi -= (n = std::min(n, cntMi));
    if(cntMi == 0){
      if(summary->empty()) mi = mx, cntMi = cntMx;
      else{
        int firstCluster = summary->minimum();
        int offset = clusters[firstCluster]->minimum(&cntMi);
        mi = index(firstCluster, offset, uSqrtLower);
        clusters[firstCluster]->remove(offset);
        if(clusters[firstCluster]->empty())
          summary->remove(firstCluster);
      }
      return deal_opt(cnt, 0), n;
    }
    else return deal_opt(cnt, cntMi), n;
  }
  else if(x == mx){ // update maximum
    cntMx -= (n = std::min(n, cntMx));
    if(cntMx == 0){
      if(summary->empty()) mx = mi, cntMx = cntMi;
      else{
        int lastCluster = summary->maximum();
        int offset = clusters[lastCluster]->maximum(&cntMx);
        mx = index(lastCluster, offset, uSqrtLower);
        clusters[lastCluster]->remove(offset);
        if(clusters[lastCluster]->empty())
          summary->remove(lastCluster);
      }
      return deal_opt(cnt, 0), n;
    }
    else return deal_opt(cnt, cntMx), n;
  }
  
  int i = high(x, uSqrtLower), j = low(x, uSqrtLower);
  n = clusters[i]->remove(j, n, cnt);
  if(clusters[i]->empty()) summary->remove(i);
  return n;
}

int VebMultiInner::extract_min(unsigned long long *cnt = nullptr){
  int x = mi;
  if(x != _veb_multi::NIL) remove(x, 1, cnt);
  else deal_opt(cnt, 0);
  return x;
}