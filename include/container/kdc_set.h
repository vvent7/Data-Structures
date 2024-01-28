#ifndef KDC_SET_H
#define KDC_SET_H

#include <cstddef> //size_t
#include <memory> //unique_ptr
#include <set> //set
#include "key_data_container.h"

template<typename Data>
class kdc_set : public key_data_container<Data, typename std::set<Data>::iterator>{
public:
  using DataLocator = typename std::set<Data>::iterator;
  kdc_set() : data(){}

  size_t size() const override { return data.size(); }
  bool empty() const override { return data.empty();}
  Data minimum() const override { return *data.begin(); }
  Data maximum() const override { return *prev(data.end()); }

  void insert(Data x, std::unique_ptr<DataLocator[]> &data2dataLoc) override {
    data2dataLoc[x] = data.insert(x).first;
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
  std::set<Data> data;
};

#endif