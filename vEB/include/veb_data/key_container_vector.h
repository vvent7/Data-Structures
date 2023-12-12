#ifndef KEY_CONTAINER_VECTOR_UNORDERED_H
#define KEY_CONTAINER_VECTOR_UNORDERED_H

#include <cstddef> //size_t
#include <vector> //vector
#include <memory> //unique_ptr

class key_container_vector_unordered{
public:
  typedef size_t Locator;
  static constexpr Locator NIL_LOCATOR = -1;

  key_container_vector_unordered() : data(){}

  size_t size() const { return data.size(); }
  bool empty() const { return data.empty(); }
  int minimum() const { return data.front(); }
  int maximum() const { return data.back(); }
  bool insert(int x, std::unique_ptr<Locator[]> &data2locator){
    if(data2locator[x] != NIL_LOCATOR) return false;
    data.push_back(x);
    data2locator[x] = data.size()-1;
    return true;
  }
  void clear(std::unique_ptr<int[]> &data2key, int NIL_KEY,  std::unique_ptr<Locator[]> &data2locator){
    for(int x : data){
      data2key[x] = NIL_KEY;
      data2locator[x] = NIL_LOCATOR;
    }
    data.clear();
  }
  bool remove(int x, std::unique_ptr<Locator[]> &data2locator){
    if(data2locator[x] == NIL_LOCATOR) return false;
    size_t idx = data2locator[x];
    data2locator[data.back()] = idx;
    data[idx] = data.back();
    data.pop_back();
    data2locator[x] = NIL_LOCATOR;
    return true;
  }
  int extract_min(std::unique_ptr<Locator[]> &data2locator){
    int x = minimum();
    remove(x, data2locator);
    return x;
  }

private:
  std::vector<int> data;
};

#endif