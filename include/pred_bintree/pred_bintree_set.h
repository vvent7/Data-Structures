#ifndef PRED_BINTREE_SET_H
#define PRED_BINTREE_SET_H

#include <cstddef> //size_t
#include <set>
#include "pred_bintree_env.h"

namespace pred_bintree{
  class Set{
  public:
    Set();

    size_t size() const;
    bool empty() const;
    key_real_t minimum() const;
    key_real_t maximum() const;
    bool member(key_real_t x) const;
    key_real_t successor(key_real_t x) const;
    key_real_t predecessor(key_real_t x) const;
    bool insert(key_real_t x);
    bool remove(key_real_t x);
    key_real_t extract_min();

  private:
    std::set<key_real_t> st;
  };
}

#endif