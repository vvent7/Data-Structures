#ifndef PRED_BITSET_SET_H
#define PRED_BITSET_SET_H

#include <cstddef> //size_t
#include <vector> //vector
#include "pred_bitset_env.h" //namespace pred_bitset

namespace pred_bitset{
  class Set{
  public:
    Set();
    Set(key_bit_t max_key);

    size_t size() const; //O(1)
    bool empty() const; //O(1)
    key_bit_t minimum(); //O(1)
    key_bit_t maximum(); //O(1)
    bool member(key_bit_t x) const; //O(n)
    key_bit_t successor(key_bit_t x) const; //O(n)
    key_bit_t predecessor(key_bit_t x) const; //O(n)
    bool insert(key_bit_t x); //O(n)
    bool remove(key_bit_t x); //O(n)
    key_bit_t extract_min(); //O(1)

  private:
    std::vector<bool> bitset; //sorted ascending
    size_t sz;
    key_bit_t max_key, mi, mx;
  };
}

#endif