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