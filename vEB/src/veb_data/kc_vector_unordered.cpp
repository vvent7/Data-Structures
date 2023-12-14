#include <cstddef> //size_t
#include <vector> //vector
#include <memory> //unique_ptr
#include "veb_data/kc_vector_unordered.h"

kc_vector_unordered::kc_vector_unordered() : data(){}

size_t kc_vector_unordered::size() const { return data.size(); }
bool kc_vector_unordered::empty() const { return data.empty(); }
int kc_vector_unordered::minimum() const { return data.back(); }
int kc_vector_unordered::maximum() const { return data.front(); }

bool kc_vector_unordered::insert(int x, std::unique_ptr<Locator[]> &data2locator){
  if(data2locator[x] != NIL_LOCATOR) return false;
  data.push_back(x);
  data2locator[x] = data.size()-1;
  return true;
}

void kc_vector_unordered::clear(std::unique_ptr<int[]> &data2key, int NIL_KEY,  std::unique_ptr<Locator[]> &data2locator){
  for(int x : data){
    data2key[x] = NIL_KEY;
    data2locator[x] = NIL_LOCATOR;
  }
  data.clear();
}

bool kc_vector_unordered::remove(int x, std::unique_ptr<Locator[]> &data2locator){
  if(data2locator[x] == NIL_LOCATOR) return false;
  size_t idx = data2locator[x];
  data2locator[data.back()] = idx;
  data[idx] = data.back();
  data.pop_back();
  data2locator[x] = NIL_LOCATOR;
  return true;
}

int kc_vector_unordered::extract_min(std::unique_ptr<Locator[]> &data2locator){
  int x = minimum();
  remove(x, data2locator);
  return x;
}