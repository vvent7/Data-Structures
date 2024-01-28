#include "utils.h"

static constexpr int INT_BITS = sizeof(int) * __CHAR_BIT__;
static constexpr int LONG_BITS = sizeof(long) * __CHAR_BIT__;
static constexpr int LONG_LONG_BITS = sizeof(long long) * __CHAR_BIT__;

int utils::msbi(unsigned int x){
  return x==0 ? -1 : (INT_BITS - __builtin_clz(x) - 1);
}
int utils::msbi(unsigned long x){
  return x==0 ? -1 : (LONG_BITS - __builtin_clzl(x) - 1);
}
int utils::msbi(unsigned long long x){
  return x==0 ? -1 : (LONG_LONG_BITS - __builtin_clzll(x) - 1);
}

int utils::lower_bound_pow2(unsigned int x){
  return x==0
    ? 0
    : __builtin_popcount(x)==1
      ? msbi(x)
      : (msbi(x)+1);
}
int utils::lower_bound_pow2(unsigned long x){
  return x==0
    ? 0
    : __builtin_popcountl(x)==1
      ? msbi(x)
      : (msbi(x)+1);
}
int utils::lower_bound_pow2(unsigned long long x){
  return x==0
    ? 0
    : __builtin_popcountll(x)==1
      ? msbi(x)
      : (msbi(x)+1);
}

int utils::upper_bound_pow2(unsigned int x){
  return x==0 ? 0 : (msbi(x)+1);
}
int utils::upper_bound_pow2(unsigned long x){
  return x==0 ? 0 : (msbi(x)+1);
}
int utils::upper_bound_pow2(unsigned long long x){
  return x==0 ? 0 : (msbi(x)+1);
}