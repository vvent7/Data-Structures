#include <cstddef>

// van Emde Boas (multi base)
class _veb_base_multi {
public:
  // Inserts x into the set. Returns the number of copies currently in the set.
  virtual int insert(int x) = 0;
  
  // Removes all copies of x from the set. Returns the number of copies removed.
  virtual int remove(int x) = 0;
  
  // Removes at most n copies of x from the set. Returns the number of copies removed.
  virtual int remove(int x, int n) = 0;

  // Returns the number of elements in the set.
  virtual int size() = 0;

  // Returns the number of copies of x in the set.
  virtual int member(int x) = 0;

  // Returns the successor of x in the set.
  virtual int successor(int x) = 0;

  // Returns the predecessor of x in the set.
  virtual int predecessor(int x) = 0;

  // Returns the minimum element in the set.
  virtual int minimum() = 0;

  // Returns the maximum element in the set.
  virtual int maximum() = 0;

  // Removes and returns the minimum element in the set (just one copy)
  virtual int extract_min() = 0;
};