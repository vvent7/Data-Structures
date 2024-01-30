#include <climits> // __CHAR_BIT__
#include "veb/veb_env.h"
#include "utils.h"

namespace veb{
  
  unsigned int upper_sqrt(unsigned int x){
    x = utils::lower_bound_pow2(x);
    return 1U << ((x+1)>>1);
  }
  unsigned long upper_sqrt(unsigned long x){
    x = utils::lower_bound_pow2(x);
    return 1UL << ((x+1)>>1);
  }
  unsigned long long upper_sqrt(unsigned long long x){
    x = utils::lower_bound_pow2(x);
    return 1ULL << ((x+1)>>1);
  }

  unsigned int lower_sqrt(unsigned int x){
    x = utils::lower_bound_pow2(x);
    return 1U << (x>>1);
  }
  unsigned long lower_sqrt(unsigned long x){
    x = utils::lower_bound_pow2(x);
    return 1UL << (x>>1);
  }
  unsigned long long lower_sqrt(unsigned long long x){
    x = utils::lower_bound_pow2(x);
    return 1ULL << (x>>1);
  }

  unsigned int high(unsigned int x, unsigned int uSqrtLower){
    return x/uSqrtLower;
  }
  unsigned long high(unsigned long x, unsigned long uSqrtLower){
    return x/uSqrtLower;
  }
  unsigned long long high(unsigned long long x, unsigned long long uSqrtLower){
    return x/uSqrtLower;
  }

  unsigned int low(unsigned int x, unsigned int uSqrtLower){
    return x%uSqrtLower;
  }
  unsigned long low(unsigned long x, unsigned long uSqrtLower){
    return x%uSqrtLower;
  }
  unsigned long long low(unsigned long long x, unsigned long long uSqrtLower){
    return x%uSqrtLower;
  }

  unsigned int index(unsigned int x, unsigned int y, unsigned int uSqrtLower){
    return x*uSqrtLower + y;
  }
  unsigned long index(unsigned long x, unsigned long y, unsigned long uSqrtLower){
    return x*uSqrtLower + y;
  }
  unsigned long long index(unsigned long long x, unsigned long long y, unsigned long long uSqrtLower){
    return x*uSqrtLower + y;
  }

  void deal_opt(unsigned long long *cnt, unsigned long long k){
    if(cnt != nullptr) *cnt = k;
  }
}
