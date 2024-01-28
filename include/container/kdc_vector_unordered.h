#ifndef KDC_VECTOR_UNORDERED_H
#define KDC_VECTOR_UNORDERED_H

#include <cstddef> //size_t
#include <memory> //unique_ptr
#include <vector> //vector
#include "key_data_container.h"

template <typename Data>
class kdc_vector_unordered final : public key_data_container<Data, size_t>{
public:
  using DataLocator = size_t;

  kdc_vector_unordered() : data(){}

  size_t size() const override { return data.size(); }
  bool empty() const override { return data.empty();}
  Data minimum() const override { return data.back(); }
  Data maximum() const override { return data.front(); }

  void insert(Data x, std::unique_ptr<DataLocator[]> &data2dataLoc) override {
    data.push_back(x);
    data2dataLoc[x] = data.size()-1;
  }

  void remove(Data x, std::unique_ptr<DataLocator[]> &data2dataLoc) override {
    DataLocator idx = data2dataLoc[x];
    data2dataLoc[data.back()] = idx;
    data[idx] = data.back();
    data.pop_back();
  }

  Data extract_min(std::unique_ptr<DataLocator[]> &data2dataLoc) override {
    Data x = minimum();
    remove(x, data2dataLoc);
    return x;
  }

  std::vector<Data> extract_all() override {
    std::vector<Data> a; //empty
    a.swap(data); //data is empty
    return a; //full
  }

private:
  std::vector<Data> data;
};

#endif