#ifndef KDC_LIST_UNORDERED_H
#define KDC_LIST_UNORDERED_H

#include <cstddef> //size_t
#include <memory> //unique_ptr
#include <list> //list
#include "key_data_container.h"

template <typename Data>
class kdc_vector_unordered final : public key_data_container<Data, size_t>{
public:
  using DataLocator = typename std::list<Data>::iterator;

  kdc_vector_unordered() : data(){}

  size_t size() const override { return data.size(); }
  bool empty() const override { return data.empty();}
  Data minimum() const override { return data.front(); }
  Data maximum() const override { return data.back(); }

  void insert(Data x, std::unique_ptr<DataLocator[]> &data2dataLoc) override {
    data.push_front(x);
    data2dataLoc[x] = data.begin();
  }

  void remove(Data x, std::unique_ptr<DataLocator[]> &data2dataLoc) override {
    data.erase(data2dataLoc[x]);
  }

  Data extract_min(std::unique_ptr<DataLocator[]> &data2dataLoc) override {
    Data x = minimum();
    remove(x, data2dataLoc);
    return x;
  }

  std::vector<Data> extract_all() override {
    std::vector<Data> a(data.begin(), data.end());
    data.clear();
    return a;
  }

private:
  std::list<Data> data;
};

#endif