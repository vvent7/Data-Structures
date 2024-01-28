#ifndef PRED_LIST_SET_H
#define PRED_LIST_SET_H

#include <cstddef> //size_t
#include <list> //list
#include "pred_list_env.h"

namespace pred_list{
  class Set{
  public:
    Set();

    size_t size() const; //O(1)
    bool empty() const; //O(1)
    key_real_t minimum() const; //O(1)
    key_real_t maximum() const; //O(1)
    bool member(key_real_t x) const; //O(n)
    key_real_t successor(key_real_t x) const; //O(n)
    key_real_t predecessor(key_real_t x) const; //O(n)
    bool insert(key_real_t x); //O(n)
    bool remove(key_real_t x); //O(n)
    key_real_t extract_min(); //O(1)

  private:
    std::list<key_real_t> list; //sorted ascending
  };
}

#endif