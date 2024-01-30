#include <cstddef> //size_t
#include <set>
#include "pred_bintree/pred_bintree_env.h"
#include "pred_bintree/pred_bintree_set.h"

namespace pred_bintree{

  Set::Set() : st(){}

  size_t Set::size() const { return st.size(); }
  bool Set::empty() const { return st.empty(); }
  key_real_t Set::minimum() const { return *st.begin(); }
  key_real_t Set::maximum() const { return *st.rbegin(); }
  bool Set::member(key_real_t x) const { return st.find(x) != st.end(); }

  key_real_t Set::successor(key_real_t x) const {
    auto it = st.upper_bound(x);
    return it == st.end() ? NIL_KEY_REAL : *it;
  }
  key_real_t Set::predecessor(key_real_t x) const {
    auto it = st.lower_bound(x);
    return it == st.begin() ? NIL_KEY_REAL : *(--it);
  }
  
  bool Set::insert(key_real_t x) {
    return st.insert(x).second;
  }
  bool Set::remove(key_real_t x) {
    return st.erase(x) > 0;
  }
  
  key_real_t Set::extract_min() {
    key_real_t x = *st.begin();
    st.erase(st.begin());
    return x;
  }

}