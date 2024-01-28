#include <algorithm> //swap
#include <memory> //unique_ptr
#include <climits> // ULLONG_MAX
#include "utils.h"
#include "veb/veb_env.h"
#include "veb/veb_multi/_veb_multi_node.h"
#include "veb/veb_multi/veb_multi_inner.h"
#include "veb/veb_multi/veb_multi_leaf.h"

namespace veb{

  MultiInner::MultiInner():
    k(0), u(0), uSqrtUpper(0), uSqrtLower(0),
    mi(NIL_KEY_BIT), mx(NIL_KEY_BIT),
    cntMi(0), cntMx(0),
    summary(nullptr), clusters(nullptr){}

  MultiInner::MultiInner(key_bit_t u):
    k(utils::lower_bound_pow2(u)),
    u(1ULL<<k),
    uSqrtUpper(upper_sqrt(u)),
    uSqrtLower(lower_sqrt(u)),
    mi(NIL_KEY_BIT), mx(NIL_KEY_BIT),
    cntMi(0), cntMx(0){

    if(u <= 2) return; //leaf 2

    clusters = std::make_unique<std::unique_ptr<_multi_node>[]>(uSqrtUpper);

    if(uSqrtUpper > BASE_U)
      summary = std::make_unique<MultiInner>(uSqrtUpper);
    else
      summary = std::make_unique<MultiLeaf>(uSqrtUpper);

    if(uSqrtLower > BASE_U){
      for(key_bit_t i=0; i<uSqrtUpper; ++i)
        clusters[i] = std::make_unique<MultiInner>(uSqrtLower);
    }
    else{
      for(key_bit_t i=0;i<uSqrtUpper; ++i)
        clusters[i] = std::make_unique<MultiLeaf>(uSqrtLower);
    }
  }

  inline bool MultiInner::empty() const {
    return mi == NIL_KEY_BIT;
  }

  key_bit_t MultiInner::minimum(unsigned long long *cnt) const {
    return deal_opt(cnt, cntMi), mi;
  }

  key_bit_t MultiInner::maximum(unsigned long long *cnt) const {
    return deal_opt(cnt, cntMx), mx;
  }

  unsigned long long MultiInner::member(key_bit_t x) const {
    if(x == mi) return cntMi;
    else if(x == mx) return cntMx;
    else if(u <= 2) return 0;
    else return clusters[high(x, uSqrtLower)]->member(low(x, uSqrtLower));
  }

  key_bit_t MultiInner::successor(key_bit_t x, unsigned long long *cnt) const {
    if(u<=2){
      return (x == 0 && mx == 1)
        ? (deal_opt(cnt, cntMx), mx)
        : (deal_opt(cnt, 0), NIL_KEY_BIT);
    }
    else if(!empty() && x < mi)
      return deal_opt(cnt, cntMi), mi;
    else{
      key_bit_t i = high(x, uSqrtLower), j = low(x, uSqrtLower);
      if(!clusters[i]->empty() && j < clusters[i]->maximum()){
        // successor is in the same cluster
        key_bit_t offset = clusters[i]->successor(j, cnt);
        return index(i, offset, uSqrtLower);
      }
      else{
        // successor is in the next cluster
        key_bit_t succCluster = summary->successor(i);

        if(succCluster == NIL_KEY_BIT){
          return (!empty() && x < mx)
            ? (deal_opt(cnt, cntMx), mx)
            : (deal_opt(cnt, 0), NIL_KEY_BIT);
        }
        else{
          key_bit_t offset = clusters[succCluster]->minimum();
          return index(succCluster, offset, uSqrtLower);
        }
      }
    }
  }

  key_bit_t MultiInner::predecessor(key_bit_t x, unsigned long long *cnt) const {
    if(u<=2){
      return (x == 1 && mi == 0)
        ? (deal_opt(cnt, cntMi), mi)
        : (deal_opt(cnt, 0), NIL_KEY_BIT);
    }
    else if(!empty() && x > mx)
      return deal_opt(cnt, cntMx), mx;
    else{
      key_bit_t i = high(x, uSqrtLower), j = low(x, uSqrtLower);
      if(!clusters[i]->empty() && j > clusters[i]->minimum()){
        // predecessor is in the same cluster
        key_bit_t offset = clusters[i]->predecessor(j, cnt);
        return index(i, offset, uSqrtLower);
      }
      else{
        // predecessor is in the previous cluster
        key_bit_t predCluster = summary->predecessor(i);

        if(predCluster == NIL_KEY_BIT){
          return (!empty() && x > mi)
            ? (deal_opt(cnt, cntMi), mi)
            : (deal_opt(cnt, 0), NIL_KEY_BIT);
        }
        else{
          key_bit_t offset = clusters[predCluster]->maximum();
          return index(predCluster, offset, uSqrtLower);
        }
      }
    }
  }

  unsigned long long MultiInner::insert(key_bit_t x, unsigned long long n, unsigned long long *cnt){
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

    key_bit_t i = high(x, uSqrtLower), j = low(x, uSqrtLower);
    if(clusters[i]->empty())
      summary->insert(i);
    
    return swapped == 0
      ? clusters[i]->insert(j, n, cnt) // not swapped
      : (clusters[i]->insert(j, n), (swapped == 1 ? cntMi : cntMx)); // swapped
  }

  unsigned long long MultiInner::remove(key_bit_t x, unsigned long long n, unsigned long long *cnt){
    if(empty() | (x < mi) | (x > mx)) return deal_opt(cnt, 0), 0;
    else if(mi == mx){ // only one element
      if(x != mi) return deal_opt(cnt, 0), 0;
      cntMi -= (n = std::min(n, cntMi));
      if(cntMi == 0) mi = NIL_KEY_BIT;
      mx = mi; cntMx = cntMi;
      return deal_opt(cnt, cntMi), n;
    }
    else if(x == mi){ // update minimum
      cntMi -= (n = std::min(n, cntMi));
      if(cntMi == 0){
        if(summary->empty()) mi = mx, cntMi = cntMx;
        else{
          key_bit_t firstCluster = summary->minimum();
          key_bit_t offset = clusters[firstCluster]->minimum(&cntMi);
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
          key_bit_t lastCluster = summary->maximum();
          key_bit_t offset = clusters[lastCluster]->maximum(&cntMx);
          mx = index(lastCluster, offset, uSqrtLower);
          clusters[lastCluster]->remove(offset);
          if(clusters[lastCluster]->empty())
            summary->remove(lastCluster);
        }
        return deal_opt(cnt, 0), n;
      }
      else return deal_opt(cnt, cntMx), n;
    }
    
    key_bit_t i = high(x, uSqrtLower), j = low(x, uSqrtLower);
    n = clusters[i]->remove(j, n, cnt);
    if(clusters[i]->empty()) summary->remove(i);
    return n;
  }

  key_bit_t MultiInner::extract_min(unsigned long long *cnt){
    key_bit_t x = mi;
    if(x != NIL_KEY_BIT) remove(x, 1, cnt);
    else deal_opt(cnt, 0);
    return x;
  }
}