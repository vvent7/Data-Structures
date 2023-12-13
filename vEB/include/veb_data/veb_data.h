#include <iostream>
#include <vector>
#include <utility> //pair
#include <cstddef> //size_t
#include <memory> //unique_ptr
#include "veb_base/veb.h"

//key: INT, data: INT

template <typename KeyContainer>
class VebData {
// static_assert(std::is_base_of<Base, T>::value, "T must derive from Base");
public:
  static const int NIL = -1;

  VebData()
    : sz(0), u(0), maxData(0), veb(),
      keyContainers(nullptr),
      data2key(nullptr),
      data2locator(nullptr){}

  VebData(int u, int maxData)
    : sz(0), u(u), maxData(maxData), veb(u),
      keyContainers(std::make_unique<KeyContainer[]>(u)),
      data2key(std::make_unique<int[]>(maxData+1)),
      data2locator(std::make_unique<typename KeyContainer::Locator[]>(maxData+1)){
        for(int i=0;i<=maxData;i++){
          data2key[i] = NIL;
          data2locator[i] = KeyContainer::NIL_LOCATOR;
        }
      }

  size_t size() const { return sz; }
  bool empty() const { return sz == 0; }

  int minimum_key() const { return empty() ? NIL : veb.minimum(); }
  int minimum_data() const {
    return empty()
      ? NIL
      : keyContainers[veb.minimum()].minimum();
  }
  std::pair<int,int> minimum() const { //key, data
    return empty() 
      ? std::make_pair(NIL,NIL)
      : std::make_pair(veb.minimum(), keyContainers[veb.minimum()].minimum());
  }

  int maximum_key() const { return empty() ? NIL : veb.maximum(); }
  int maximum_data() const {
    return empty()
      ? NIL
      : keyContainers[veb.maximum()].maximum();
  }
  std::pair<int,int> maximum() const { //key, data
    return empty() 
      ? std::make_pair(NIL,NIL)
      : std::make_pair(veb.maximum(), keyContainers[veb.maximum()].maximum());
  }

  bool member_key(int key) const { return keyContainers[key].empty(); } //O(1)
  bool member_data(int data) const { return data2key[data]!=NIL; } //O(1)
  bool member(int key, int data) const { return data2key[data]==key; } //O(1)

  int get_key(int data) const { return data2key[data]; }
  const KeyContainer& get_key_container(int key) const { return keyContainers[key]; }

  int successor_key(int key) const {
    int succ = veb.successor(key);
    return succ == _veb::NIL ? NIL : succ;
  }
  int predecessor_key(int key) const {
    int pred = veb.predecessor(key);
    return pred == _veb::NIL ? NIL : pred;
  }

  bool insert(int key, int data){
    if(member_data(data)) return false;
    if(!keyContainers[key].insert(data, data2locator)) return false;
    if(keyContainers[key].size() == 1) veb.insert(key);
    data2key[data] = key;
    sz++;
    return true;
  }

  size_t remove_key(int key){
    size_t n = keyContainers[key].size();
    if(n == 0) return 0;
    keyContainers[key].clear(data2key, NIL, data2locator);
    veb.remove(key);
    sz -= n;
    return n;
  }
  bool remove_data(int data){
    int key = data2key[data];
    if(key == NIL) return false;
    keyContainers[key].remove(data, data2locator);
    if(keyContainers[key].empty()) veb.remove(key);
    data2key[data] = NIL;
    sz--;
    return true;
  }


  int extract_min_data(){
    return extract_min().second;
  }
  std::pair<int,int> extract_min(){ //key, data
    if(empty()) return {NIL,NIL};
    int key = veb.extract_min();
    int data = keyContainers[key].extract_min(data2locator);
    data2key[data] = NIL;
    sz--;
    return {key, data};
  }

private:
  size_t sz;
  int u, maxData;
  Veb veb;
  std::unique_ptr<KeyContainer[]> keyContainers; //key -> data1, data2, data3...
  std::unique_ptr<int[]> data2key; //data -> key
  std::unique_ptr<typename KeyContainer::Locator []> data2locator; //DO NOT TOUCH (only for KeyContainer)
};