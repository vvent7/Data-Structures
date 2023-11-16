#include<iostream>
#include "veb.h"
#include "utils.h"

Veb::Veb():
  k(0), u(0), uSqrtUpper(0), uSqrtLower(0){}

Veb::Veb(int u):
  k(first_power_of_2(u)),
  u(1<<k),
  uSqrtUpper(upper_sqrt(u)),
  uSqrtLower(lower_sqrt(u)),
  mi(Veb::NIL), mx(Veb::NIL){

  if(u <= 2) return; // base case

  summary = std::make_unique<Veb>(uSqrtUpper);

  cluster = std::make_unique<Veb[]>(uSqrtUpper);
  for(int i=0; i<uSqrtUpper; i++)
    cluster[i] = Veb(uSqrtLower);
}

bool Veb::insert(int x){
  if(mi == Veb::NIL) // empty set
    return (mi = mx = x), true;

  if(x==mi) return false; // already inserted

  bool inserted = false;
  if(x < mi){ // update minimum
    std::swap(x, mi);
    inserted = true;
  }

  if(u > 2){ // not a base case
    int i = high(x), j = low(x);
    if(cluster[i].minimum() == Veb::NIL)
      summary->insert(i);
    inserted = cluster[i].insert(j);
  }
  if(x > mx) mx = x, inserted = true;
  return inserted;
}

bool Veb::remove(int x){
  if(mi == Veb::NIL) return false; // empty set
  else if(mi == mx) // only one element
    return x != mi ? false : (mi = mx = Veb::NIL, true);
  else if(u <= 2){ // base case (2 elements exists)
    if(x == 0) return mi = 1, true;
    else if(x == 1) return mx = 0, true;
    return false;
  }
  else if(x == mi){ // update minimum
    int firstCluster = summary->minimum();
    x = mi = index(firstCluster, cluster[firstCluster].minimum());
  }

  int i = high(x), j = low(x);
  bool removed = cluster[i].remove(j);

  if(!removed) return false;

  // update summary (cluster[i] emptied)
  if(cluster[i].minimum() == Veb::NIL){
    summary->remove(i);
    if(x == mx){ // update maximum (x was the maximum)
      int summaryMax = summary->maximum();
      if(summaryMax == Veb::NIL) mx = mi;
      else mx = index(summaryMax, cluster[summaryMax].maximum());
    }
  }
  else if(x == mx) // update maximum (x was the maximum)
    mx = index(i, cluster[i].maximum());

  return true;
}

bool Veb::member(int x){
  if(x == mi || x == mx) return true;
  else if(u <= 2) return false;
  else return cluster[high(x)].member(low(x));
}

int Veb::successor(int x){
  if(u<=2){
    if(x == 0 && mx == 1) return 1;
    else return Veb::NIL;
  }
  else if(mi != Veb::NIL && x < mi) return mi;
  else{
    int i = high(x), j = low(x);
    int maxLow = cluster[i].maximum();

    if(maxLow != Veb::NIL && j < maxLow){
      int offset = cluster[i].successor(j);
      return index(i, offset);
    }
    else{
      int succCluster = summary->successor(i);
      if(succCluster == Veb::NIL) return Veb::NIL;
      else{
        int offset = cluster[succCluster].minimum();
        return index(succCluster, offset);
      }
    }
  }
}

int Veb::predecessor(int x){
  if(u<=2){
    if(x == 1 && mi == 0) return 0;
    else return Veb::NIL;
  }
  else if(mx != Veb::NIL && x > mx) return mx;
  else{
    int i = high(x), j = low(x);
    int minLow = cluster[i].minimum();

    if(minLow != Veb::NIL && j > minLow){
      int offset = cluster[i].predecessor(j);
      return index(i, offset);
    }
    else{
      int predCluster = summary->predecessor(i);
      if(predCluster == Veb::NIL)
        return (mi != Veb::NIL && x > mi) ? mi : Veb::NIL;
      else{
        int offset = cluster[predCluster].maximum();
        return index(predCluster, offset);
      }
    }
  }
}

int Veb::minimum(){
  return mi;
}

int Veb::maximum(){
  return mx;
}

int Veb::extract_min(){
  int x = mi;
  if(x != Veb::NIL) remove(x);
  return x;
}


//==========PRIVATE==========
inline int Veb::high(int x){
  return x/uSqrtLower;
}
inline int Veb::low(int x){
  return x%uSqrtLower;
}
inline int Veb::index(int x, int y){
  return x*uSqrtLower + y;
}