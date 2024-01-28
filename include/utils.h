#ifndef UTILS_H
#define UTILS_H

namespace utils{
  // most significant bit index
  int msbi(unsigned int x);
  int msbi(unsigned long x);
  int msbi(unsigned long long x);

  // smallest k:  2^k >= x
  int lower_bound_pow2(unsigned int x);
  int lower_bound_pow2(unsigned long x);
  int lower_bound_pow2(unsigned long long x);

  // smallest k:  2^k > x
  int upper_bound_pow2(unsigned int x);
  int upper_bound_pow2(unsigned long x);
  int upper_bound_pow2(unsigned long long x);
};

#endif