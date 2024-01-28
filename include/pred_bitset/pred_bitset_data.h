#ifndef PRED_BITSET_DATA_H
#define PRED_BITSET_DATA_H

#include <utility> //pair
#include <stddef.h> //size_t
#include <memory> //unique_ptr
#include "pred_bitset_env.h"
#include "pred_bitset_set.h"

namespace pred_bitset {

  template <template<typename data> typename data_container>
  class Data {
    using DataContainer = data_container<data_t>;
    using ContainerLocator = key_bit_t;
  public:
    Data()
      : sz(0), maxKey(0), maxData(0), predBs(),
        containers(nullptr),
        data2containerLoc(nullptr),
        data2dataLoc(nullptr){}

    Data(key_bit_t maxKey, data_t maxData)
      : sz(0), maxKey(maxKey), maxData(maxData),
        predBs(maxKey+1),
        containers(std::make_unique<DataContainer[]>(maxKey+1)),
        data2containerLoc(std::make_unique<ContainerLocator[]>(maxData+1)),
        data2dataLoc(std::make_unique<typename DataContainer::DataLocator[]>(maxData+1)){
          for(data_t i=0;i<=maxData;++i)
            data2containerLoc[i] = NIL_KEY_BIT;
        }

    size_t size() const { return sz; }
    bool empty() const { return sz == 0; }

    key_bit_t minimum_key() { return predBs.minimum(); }
    data_t minimum_data(key_bit_t key) {
      return containers[key].empty() ? NIL_DATA : containers[key].minimum();
    }
    data_t minimum_data() {
      return empty() ? NIL_DATA : containers[predBs.minimum()].minimum();
    }
    std::pair<key_bit_t,data_t> minimum() { //key, data
      return std::make_pair(minimum_key(), minimum_data());
    }

    key_bit_t maximum_key() { return predBs.maximum(); }
    data_t maximum_data(key_bit_t key) {
      return containers[key].empty() ? NIL_DATA : containers[key].maximum();
    }
    data_t maximum_data() {
      return empty() ? NIL_DATA : containers[predBs.maximum()].maximum();
    }
    std::pair<key_bit_t,data_t> maximum() { //key, data
      return std::make_pair(maximum_key(), maximum_data());
    }

    bool member_key(key_bit_t key) const { return !containers[key].empty(); } //O(1)
    bool member_data(data_t data) const { return data2containerLoc[data]!=NIL_KEY_BIT; } //O(1)
    bool member(key_bit_t key, data_t data) const { return data2containerLoc[data]==key; } //O(1)

    key_bit_t get_key(data_t data) const { return data2containerLoc[data]; }
    const DataContainer& get_key_container(key_bit_t key) const { return containers[key]; }

    key_bit_t successor_key(key_bit_t key) const {
      return predBs.successor(key);
    }
    key_bit_t predecessor_key(key_bit_t key) const {
      return predBs.predecessor(key);
    }

    bool insert(key_bit_t key, data_t data){
      if(member_data(data)) return false;
      if(!member_key(key)) predBs.insert(key);
      containers[key].insert(data, data2dataLoc);
      data2containerLoc[data] = key;
      ++sz;
      return true;
    }

    size_t remove_key(key_bit_t key){
      size_t n = containers[key].size();
      if(n == 0) return 0;
      std::vector v = containers[key].extract_all();
      for(auto data : v) data2containerLoc[data] = NIL_KEY_BIT;
      predBs.remove(key);
      sz -= n;
      return n;
    }
    bool remove_data(data_t data){
      key_bit_t key = data2containerLoc[data];
      if(key == NIL_KEY_BIT) return false;
      containers[key].remove(data, data2dataLoc);
      if(containers[key].empty()) predBs.remove(key);
      data2containerLoc[data] = NIL_KEY_BIT;
      --sz;
      return true;
    }
    
    bool change_key(data_t data, key_bit_t newKey){
      if(!remove_data(data)) return false;
      return insert(newKey, data);
    }
    bool decrease_key(data_t data, key_bit_t newKey){
      if(get_key(data) <= newKey) return false;
      return change_key(data, newKey);
    }

    data_t extract_min_data(key_bit_t key){
      if(!member_key(key)) return NIL_DATA;
      data_t data = containers[key].extract_min(data2dataLoc);
      if(containers[key].empty()) predBs.remove(key);
      data2containerLoc[data] = NIL_KEY_BIT;
      --sz;
      return data;
    }

    std::pair<key_bit_t,data_t> extract_min(){ //key, data
      if(empty()) return {NIL_KEY_BIT, NIL_DATA};
      key_bit_t key = minimum_key();
      return {key, extract_min_data(key)};
    }
    key_bit_t extract_min_key(){
      return extract_min().first;
    }
    data_t extract_min_data(){
      return extract_min().second;
    }    

  private:
    size_t sz;
    key_bit_t maxKey;
    data_t maxData;
    Set predBs;
    std::unique_ptr<DataContainer[]> containers; //key -> data1, data2, data3...
    std::unique_ptr<ContainerLocator[]> data2containerLoc; //data -> key (index)
    std::unique_ptr<typename DataContainer::DataLocator []> data2dataLoc; //(only for DataContainer)
  };

}

#endif