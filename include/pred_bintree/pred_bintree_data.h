#ifndef PRED_BINTREE_DATA_H
#define PRED_BINTREE_DATA_H

#include <cstddef> //size_t
#include <set> //set
#include <vector> //vector
#include <utility> //pair
#include "pred_bintree_env.h"

namespace pred_bintree{
  class Data{
  public:
    Data(data_t maxData);
    Data(key_real_t maxKey, data_t maxData); //maxKey is not used

    size_t size() const;
    bool empty() const;

    key_real_t minimum_key() const;
    data_t minimum_data() const;
    std::pair<key_real_t,data_t> minimum() const;

    key_real_t maximum_key();
    data_t maximum_data() const;
    std::pair<key_real_t,data_t> maximum() const;

    bool member_key(key_real_t key) const ;
    bool member_data(data_t data) const ;
    bool member(key_real_t key, data_t data) const;

    key_real_t get_key(data_t data) const ;

    key_real_t successor_key(key_real_t key) const;
    key_real_t predecessor_key(key_real_t key) const;

    bool insert(key_real_t key, data_t data);

    size_t remove_key(key_real_t key);
    bool remove_data(data_t data);
    
    bool change_key(key_real_t newKey, data_t data);
    bool decrease_key(key_real_t newKey, data_t data);

    std::pair<key_real_t,data_t> extract_min(); //KEY,DATA
    key_real_t extract_min_key();
    data_t extract_min_data();

  private:
    data_t maxData;
    std::set<std::pair<key_real_t,data_t>> st;
    std::vector<std::set<std::pair<key_real_t,data_t>>::iterator> data2it;
  };
}

#endif