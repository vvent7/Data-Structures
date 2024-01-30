#include <cstddef> //size_t
#include <set> //set
#include <vector> //vector
#include <utility> //pair
#include "pred_bintree/pred_bintree_env.h"
#include "pred_bintree/pred_bintree_data.h"

namespace pred_bintree{

  Data::Data(data_t maxData)
    : maxData(maxData), st(), data2it(maxData+1, st.end()) {}

  Data::Data(key_real_t maxKey, data_t maxData)
    : Data(maxData) {}

  size_t Data::size() const { return st.size(); }
  bool Data::empty() const { return st.empty(); }

  key_real_t Data::minimum_key() const { return st.begin()->first; }
  data_t Data::minimum_data() const { return st.begin()->second; }
  std::pair<key_real_t,data_t> Data::minimum() const { return *st.begin(); }

  key_real_t Data::maximum_key() { return st.rbegin()->first; }
  data_t Data::maximum_data() const { return st.rbegin()->second; }
  std::pair<key_real_t,data_t> Data::maximum() const { return *st.rbegin(); }

  bool Data::member_key(key_real_t key) const {
    auto it = st.lower_bound({key,0});
    return it!=st.end() && it->first==key;
  }
  bool Data::member_data(data_t data) const {
    return data<=maxData && data2it[data]!=st.end();
  }
  bool Data::member(key_real_t key, data_t data) const {
    return member_data(data) && data2it[data]->first==key;
  }

  key_real_t Data::get_key(data_t data) const {
    return data2it[data]->first;
  }

  key_real_t Data::successor_key(key_real_t key) const {
    auto it = st.lower_bound({key+1,0});
    return it==st.end() ? NIL_KEY_REAL : it->first;
  }
  key_real_t Data::predecessor_key(key_real_t key) const {
    auto it = st.lower_bound({key,0});
    return it==st.begin() ? NIL_KEY_REAL : (--it)->first;
  }

  bool Data::insert(key_real_t key, data_t data) {
    if(data > maxData || data2it[data]!=st.end()) return false;
    data2it[data] = st.emplace(key,data).first;
    return true;
  }

  size_t Data::remove_key(key_real_t key) {
    auto beg = st.lower_bound({key,0}), end = st.lower_bound({key+1,0});
    size_t n = 0;
    for(auto it = beg; it != end; ++it){
      data2it[it->second] = st.end();
      ++n;
    }
    st.erase(beg,end);
    return n;
  }
  bool Data::remove_data(data_t data) {
    if(!member_data(data)) return false;
    st.erase(data2it[data]);
    data2it[data] = st.end();
    return true;
  }

  bool Data::change_key(key_real_t newKey, data_t data) {
    return remove_data(data) && insert(newKey,data);
  }
  bool Data::decrease_key(key_real_t newKey, data_t data) {
    if(!member_data(data)) return false;
    if(newKey >= data2it[data]->first) return false;
    return change_key(newKey,data);
  }

  std::pair<key_real_t,data_t> Data::extract_min() {
    auto it = st.begin();
    auto p = *it;
    data2it[p.second] = st.end();
    st.erase(it);
    return p;
  }
  key_real_t Data::extract_min_key() {
    return extract_min().first;
  }
  data_t Data::extract_min_data() {
    return extract_min().second;
  }

}