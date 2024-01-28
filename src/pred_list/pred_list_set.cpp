#include <cstddef> //size_t
#include "pred_list/pred_list_set.h"

namespace pred_list {

  Set::Set()
    : list(){}

  size_t Set::size() const { return list.size(); }

  bool Set::empty() const { return list.empty(); }

  key_real_t Set::minimum() const {
    return list.empty() ? NIL_KEY_REAL : list.front();
  }

  key_real_t Set::maximum() const {
    return list.empty() ? NIL_KEY_REAL : list.back();
  }

  bool Set::member(key_real_t x) const {
    for(auto it=list.begin();it!=list.end();++it){
      if(*it == x) return true;
      else if(*it > x) return false;
    }
    return false;
  }

  key_real_t Set::successor(key_real_t x) const {
    for(auto it=list.begin();it!=list.end();++it){
      if(*it > x) return *it;
    }
    return NIL_KEY_REAL;
  }

  key_real_t Set::predecessor(key_real_t x) const {
    for(auto it=list.rbegin();it!=list.rend();++it){
      if(*it < x) return *it;
    }
    return NIL_KEY_REAL;
  }

  bool Set::insert(key_real_t x) {
    auto it = list.begin();
    for(;it!=list.end();++it){
      if(*it == x) return false;
      else if(*it > x) break;
    }

    list.insert(it, x);

    return true;
  }

  bool Set::remove(key_real_t x) {
    auto it = list.begin();
    for(;it!=list.end();++it){
      if(*it == x) break;
      else if(*it > x) return false;
    }

    list.erase(it);

    return true;
  }

  key_real_t Set::extract_min() {
    if(list.empty()) return NIL_KEY_REAL;
    key_real_t min = list.front();
    list.pop_front();
    return min;
  }
}