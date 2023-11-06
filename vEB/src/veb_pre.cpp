#include "veb_pre.h"
#include "utils.h"

VebPre::VebPre(size_t u):
  k((first_power_of_2(u)+1) >> 1),
  u(1<<(k<<1)),
  uSqrt(1<<k),
  n(0),
  a(this->u, false),
  summary(uSqrt, false){ }

void VebPre::insert(int x){
  if(a[x]) return; // already inserted

  int i = x/uSqrt; // high order bits
  a[x] = summary[i] = true;
  n++;
}

void VebPre::remove(int x){
  if(!a[x]) return; // not inserted

  a[x] = false;
  n--;

  // update summary
  int i = x/uSqrt; // high order bits
  bool oneTrue = false;
  for(int j=0; j<uSqrt; j++){
    if(a[i*uSqrt+j]){
      oneTrue = true;
      break;
    }
  }
  summary[i] = oneTrue;
}

size_t VebPre::size(){
  return n;
}

bool VebPre::member(int x){
  return a[x];
}

int VebPre::successor(int x){
  int i = x/uSqrt; // high order bits

  //searching in same cluster
  if(summary[i]){
    int j = x%uSqrt; // low order bits
    for(int l=j+1; l<uSqrt; l++){
      if(a[i*uSqrt+l]) return i*uSqrt+l;
    }
  }

  //searching in next clusters
  for(int l=i+1; l<uSqrt; l++){
    if(!summary[l]) continue;
    
    for(int m=0; m<uSqrt; m++){
      if(a[l*uSqrt+m]) return l*uSqrt+m;
    }
  }

  return -1; // not found
}

int VebPre::predecessor(int x){
  int i = x/uSqrt; // high order bits

  //searching in same cluster
  if(summary[i]){
    int j = x%uSqrt; // low order bits
    for(int l=j-1; l>=0; l--){
      if(a[i*uSqrt+l]) return i*uSqrt+l;
    }
  }

  //searching in previous clusters
  for(int l=i-1; l>=0; l--){
    if(!summary[l]) continue;
    
    for(int m=uSqrt-1; m>=0; m--){
      if(a[l*uSqrt+m]) return l*uSqrt+m;
    }
  }

  return -1; // not found
}

int VebPre::minimum(){
  if(n==0) return -1; // empty set

  for(int i=0; i<uSqrt; i++){
    if(!summary[i]) continue;

    for(int j=0; j<uSqrt; j++){
      if(a[i*uSqrt+j]) return i*uSqrt+j;
    }
  }

  return -1; // not found
}

int VebPre::maximum(){
  if(n==0) return -1; // empty set

  for(int i=uSqrt-1; i>=0; i--){
    if(!summary[i]) continue;

    for(int j=uSqrt-1; j>=0; j--){
      if(a[i*uSqrt+j]) return i*uSqrt+j;
    }
  }

  return -1; // not found
}