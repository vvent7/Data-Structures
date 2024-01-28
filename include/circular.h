#ifndef CIRCULAR_H
#define CIRCULAR_H

#include <utility> //pair
#include <cstddef> //size_t
#include "env.h"

  using namespace env;
template <typename Container>
class Circular {
public:

  Circular()
    : container(),
      maxJump(0), last(0), mi(0), mx(0), cycle(0){}
  
  Circular(key_bit_t maxJump, data_t maxData)
    : container(maxJump+1, maxData),
      maxJump(maxJump), last(0), mi(0), mx(0), cycle(0){}
  
  size_t size() const { return container.size(); }
  bool empty() const { return container.empty(); }

  key_bit_t minimum_key() {
    if(empty()) return NIL_KEY_BIT;
    if(container.member_key(mi)) return mi;
    if(container.maximum_key() >= mi)
      return mi = container.successor_key(mi); 
    return mi = container.minimum_key();
  }
  data_t minimum_data() {
    return empty() ? NIL_DATA : container.minimum_data(minimum_key());
  }
  std::pair<key_bit_t,data_t> minimum() { //key, data
    return std::make_pair(minimum_key(), minimum_data());
  }

  key_bit_t maximum_key() {
    if(empty()) return NIL_KEY_BIT;
    if(container.member_key(mx)) return mx;
    if(container.minimum_key() <= mx)
      return mx = container.predecessor_key(mx);
    return mx = container.maximum_key();
  }
  data_t maximum_data() {
    return empty() ? NIL_DATA : container.maximum_data(maximum_key());
  }
  std::pair<key_bit_t,data_t> maximum() { //key, data
    return std::make_pair(maximum_key(), maximum_data());
  }

  bool member_key(key_bit_t key) const { return container.member_key(key); }
  bool member_data(data_t data) const { return container.member_data(data); }
  bool member(key_bit_t key, data_t data) const { return container.member(key, data); }

  key_bit_t get_key(data_t data) const { return container.get_key(data); }
  const Container& get_key_container(key_bit_t key) const { return container.get_key_container(key); }

  key_bit_t successor_key(key_bit_t key) const {
    return container.successor_key(key);
  }
  key_bit_t predecessor_key(key_bit_t key) const {
    return container.predecessor_key(key);
  }

  bool insert(key_bit_t key, data_t data){
    if(!container.insert(key, data)) return false;
    if(isLess(mx,key)) mx = key; //mx < key (updating max)
    if(isLess(key,mi)) mi = key; //key < mi (updating min)
    return true;
  }

  size_t remove_key(key_bit_t key){
    return container.remove_key(key);
  }
  bool remove_data(data_t data){
    return container.remove_data(data);
  }
  
  bool change_key(data_t data, key_bit_t newKey){
    bool changed = container.change_key(data, newKey);
    if(changed){
      if(isLess(newKey,mi)) mi = newKey; //newKey < mi (updating min
      if(isLess(mx,newKey)) mx = newKey; //mx < newKey (updating max)
    }
    return changed;
  }
  bool decrease_key(data_t data, key_bit_t newKey){
    bool changed = container.decrease_key(data, newKey);
    if(changed && isLess(newKey,mi)) mi = newKey; //newKey < mi (updating min)
    return changed;
  }

  std::pair<key_bit_t,data_t> extract_min(){ //key, data
    if(empty()) return {NIL_KEY_BIT, NIL_DATA};
    key_bit_t key = minimum_key();
    data_t data = container.extract_min_data(key);
    if(key < last) ++cycle;
    last = key;
    return {key, data};
  }
  key_bit_t extract_min_key(){
    return extract_min().first;
  }
  data_t extract_min_data(){
    return extract_min().second;
  }

  key_real_t toRealKey(key_bit_t x){
    key_real_t key = x + cycle * (maxJump + 1);
    if(x<last) key += maxJump + 1;
    return key;
  }
  key_bit_t toRelativeKey(key_bit_t x){
    if(x>=last) return x - last;
    return x + (maxJump + 1 - last);
  }
  key_bit_t toBitKey(key_bit_t x){
    // return x % (maxJump + 1); //(reliable, slow)
    return x > maxJump ? (x-maxJump-1) : x; //(unreliable, faster)
  }

private:
  Container container;
  key_bit_t maxJump, last, mi, mx;
  key_real_t cycle;

  /*
    maxJump: container maxKey
    last: last removed key
    mi: minimum current key (last<=mi)
    mx: maximum current key (mi<=mx)
    cycle: number of complete cycles (maxJump+1)
  */

  
  bool isLess(key_bit_t x, key_bit_t y){
    return toRelativeKey(x) < toRelativeKey(y);
  }
  bool isEqual(key_bit_t x, key_bit_t y){
    return toRelativeKey(x) == toRelativeKey(y);
  }
  bool isGreater(key_bit_t x, key_bit_t y){
    return toRelativeKey(x) > toRelativeKey(y);
  }

};


#endif