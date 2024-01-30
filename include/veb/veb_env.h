#ifndef VEB_ENV_H
#define VEB_ENV_H

#include <climits> // __CHAR_BIT__
#include "env.h"

namespace veb{
  using namespace env;
  
  static constexpr key_bit_t BASE_U = sizeof(unsigned long long) * __CHAR_BIT__;

  // 2 ^ ceil(log(first_power_of_2(x))/2)
  unsigned int upper_sqrt(unsigned int x);
  unsigned long upper_sqrt(unsigned long x);
  unsigned long long upper_sqrt(unsigned long long x);

  // 2 ^ floor(log(first_power_of_2(x))/2)
  unsigned int lower_sqrt(unsigned int x);
  unsigned long lower_sqrt(unsigned long x);
  unsigned long long lower_sqrt(unsigned long long x);

  unsigned int high(unsigned int x, unsigned int uSqrtLower);
  unsigned long high(unsigned long x, unsigned long uSqrtLower);
  unsigned long long high(unsigned long long x, unsigned long long uSqrtLower);

  unsigned int low(unsigned int x, unsigned int uSqrtLower);
  unsigned long low(unsigned long x, unsigned long uSqrtLower);
  unsigned long long low(unsigned long long x, unsigned long long uSqrtLower);

  unsigned int index(unsigned int x, unsigned int y, unsigned int uSqrtLower);
  unsigned long index(unsigned long x, unsigned long y, unsigned long uSqrtLower);
  unsigned long long index(unsigned long long x, unsigned long long y, unsigned long long uSqrtLower);

  void deal_opt(unsigned long long *cnt, unsigned long long k);
}

#endif