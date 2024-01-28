#ifndef PRED_LIST_DATA_H
#define PRED_LIST_DATA_H

#include <utility> //pair
#include <stddef.h> //size_t
#include <memory> //unique_ptr
#include <list> //list
#include <vector> //vector
#include "pred_list_env.h"

namespace pred_list{

  template <template<typename data> typename data_container>
  class Data{
  public:
    Data()
      : sz(0), maxData(0), containers(),
        data2containerLoc(nullptr),
        data2dataLoc(nullptr){}
    
    Data(data_t maxData)
      : sz(0), maxData(maxData),
        containers(),
        NIL_LOC(containers.end()),
        data2containerLoc(std::make_unique<ContainerLocator[]>(maxData+1)),
        data2dataLoc(std::make_unique<typename DataContainer::DataLocator[]>(maxData+1)){
          for(data_t i=0;i<=maxData;++i)
            data2containerLoc[i] = NIL_LOC;
        }
    
    size_t size() const { return sz; }
    bool empty() const { return sz == 0; }

    key_real_t minimum_key() const { return empty() ? NIL_KEY_REAL : containers.front().key; }
    data_t minimum_data() const { return empty() ? NIL_DATA : containers.front().dataContainer.minimum(); }
    std::pair<key_real_t,data_t> minimum() const { //key, data
      return std::make_pair(minimum_key(), minimum_data());
    }

    key_real_t maximum_key() const { return empty() ? NIL_KEY_REAL : containers.back().key; }
    data_t maximum_data() const { return empty() ? NIL_DATA : containers.back().dataContainer.maximum(); }
    std::pair<key_real_t,data_t> maximum() const { //key, data
      return std::make_pair(maximum_key(), maximum_data());
    }

    bool member_data(data_t data) const { return data2containerLoc[data]!=NIL_LOC; } //O(1)
    bool member(key_real_t key, data_t data) const { //O(1)
      return member_data(data) && data2containerLoc[data]->key==key;
    }

    key_real_t get_key(data_t data) const {
      return member_data(data) ? data2containerLoc[data]->key : NIL_KEY_REAL;
    }

    key_real_t successor_key(key_real_t key) const {
      auto it = containers.begin();
      for(;it!=containers.end();++it){
        if(it->key > key) return it->key;
      }
      return NIL_KEY_REAL;
    }
    key_real_t predecessor_key(key_real_t key) const {
      auto it = containers.rbegin();
      for(;it!=containers.rend();++it){
        if(it->key < key) return it->key;
      }
      return NIL_KEY_REAL;
    }

    bool insert(key_real_t key, data_t data){
      if(member_data(data)) return false;

      auto it = containers.begin();
      for(;it!=containers.end();++it){
        if(it->key == key) break;
        else if(it->key > key) break;
      }
      if(it == containers.end() || it->key != key){
        it = containers.insert(it, {key, DataContainer()});
      }
      it->dataContainer.insert(data, data2dataLoc);
      data2containerLoc[data] = it;
      ++sz;
      return true;
    }
    
    size_t remove_key(key_real_t key){
      auto it = containers.begin();
      for(;it!=containers.end();++it){
        if(it->key == key) break;
        else if(it->key > key) return 0;
      }
      std::vector v = it->dataContainer.extract_all();
      for(auto data : v) data2containerLoc[data] = NIL_LOC;
      containers.erase(it);
      sz -= v.size();
      return v.size();
    }
    bool remove_data(data_t data){
      auto it = data2containerLoc[data];
      if(it == NIL_LOC) return false;
      it->dataContainer.remove(data, data2dataLoc);
      if(it->dataContainer.empty()) containers.erase(it);
      data2containerLoc[data] = NIL_LOC;
      --sz;
      return true;
    }

    bool change_key(data_t data, key_real_t newKey){
      if(!remove_data(data)) return false;
      return insert(newKey, data);
    }
    bool decrease_key(data_t data, key_real_t newKey){
      if(get_key(data) <= newKey) return false;
      return change_key(data, newKey);
    }

    std::pair<key_real_t,data_t> extract_min(){
      if(empty()) return std::make_pair(NIL_KEY_REAL, NIL_DATA);
      auto it = containers.begin();
      key_real_t key = it->key;
      data_t data = it->dataContainer.extract_min(data2dataLoc);
      if(it->dataContainer.empty()) containers.erase(it);
      data2containerLoc[data] = NIL_LOC;
      --sz;
      return std::make_pair(key, data);
    }
    key_real_t extract_min_key(){
      return extract_min().first;
    }
    data_t extract_min_data(){
      return extract_min().second;
    }

  private:
    using DataContainer = data_container<data_t>;
    struct Container{ key_real_t key; DataContainer dataContainer; };
    using ContainerLocator = typename std::list<Container>::iterator;

    size_t sz;
    data_t maxData;
    std::list<Container> containers; // {key, dataContainer} ascending key order
    ContainerLocator NIL_LOC;
    std::unique_ptr<ContainerLocator[]> data2containerLoc; //data -> Container (ListItem)
    std::unique_ptr<typename DataContainer::DataLocator[]> data2dataLoc; //data -> DataLoc (in DataContainer)
  };

}

#endif