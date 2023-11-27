#include "utils.h"

int msbi(int x){
  return x==0 ? -1 : 31 - __builtin_clz(x);
}

int first_power_of_2(int x){
  return x==0
    ? 0
    : __builtin_popcount(x)==1
      ? msbi(x)
      : msbi(x)+1;
}

int upper_sqrt(int x){
  x = first_power_of_2(x);
  return 1 << ((x+1)>>1);
}

int lower_sqrt(int x){
  x = first_power_of_2(x);
  return 1 << (x>>1);
}


inline int high(int x, int uSqrtLower){
  return x/uSqrtLower;
}
inline int low(int x, int uSqrtLower){
  return x%uSqrtLower;
}
inline int index(int x, int y, int uSqrtLower){
  return x*uSqrtLower + y;
}