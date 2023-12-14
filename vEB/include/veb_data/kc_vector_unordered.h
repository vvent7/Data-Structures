#ifndef KEY_CONTAINER_VECTOR_UNORDERED_H
#define KEY_CONTAINER_VECTOR_UNORDERED_H

#include <cstddef> //size_t
#include <vector> //vector
#include <memory> //unique_ptr

class kc_vector_unordered{
public:
  typedef size_t Locator;
  static constexpr Locator NIL_LOCATOR = -1;

  kc_vector_unordered();

  size_t size() const;
  bool empty() const;
  int minimum() const;
  int maximum() const;

  bool insert(int x, std::unique_ptr<Locator[]> &data2locator);

  void clear(std::unique_ptr<int[]> &data2key, int NIL_KEY,  std::unique_ptr<Locator[]> &data2locator);

  bool remove(int x, std::unique_ptr<Locator[]> &data2locator);

  int extract_min(std::unique_ptr<Locator[]> &data2locator);

private:
  std::vector<int> data;
};

#endif