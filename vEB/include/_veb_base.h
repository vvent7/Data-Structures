#include <cstddef>

// van Emde Boas (base)
class _veb_base {
public:
  // Inserts x into the set. Returns true if x was inserted, false if x was already in the set.
  virtual bool insert(int x) = 0;

  // Removes x from the set. Returns true if x was removed, false if x was not in the set.
  virtual bool remove(int x) = 0;

  // Returns the number of elements in the set.
  virtual int size() = 0;

  // Returns true if x is in the set, false otherwise.
  virtual bool member(int x) = 0;

  // Returns the successor of x in the set.
  virtual int successor(int x) = 0;

  // Returns the predecessor of x in the set.
  virtual int predecessor(int x) = 0;

  // Returns the minimum element in the set.
  virtual int minimum() = 0;

  // Returns the maximum element in the set.
  virtual int maximum() = 0;

  // Removes and returns the minimum element in the set
  virtual int extract_min() = 0;
};