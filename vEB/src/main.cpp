#include <iostream>
#include "veb_base/veb.h"
#include "veb_multi/veb_multi.h"
#include "veb_data/veb_data.h"
#include "veb_data/key_container_vector.h"
#define _ ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define endl '\n'
using namespace std;

int main(){_
  // int u, n;
  // cin>>u>>n;

  VebData<key_container_vector_unordered> vebData(1e6, 1e6);

  cout<<vebData.insert(1, 1)<<endl;
  vebData.insert(2, 2);
  vebData.insert(1, 0);
  // 1: 1 0
  // 2: 2
  cout<<vebData.extract_min_data()<<endl;
  vebData.insert(0, 3);
  vebData.insert(1, 5);
  cout<<vebData.extract_min_data()<<endl;
  vebData.remove_key(1);
  cout<<vebData.extract_min_data()<<endl;
  cout<<vebData.empty()<<endl;
  // Veb *veb = new Veb(u);

  // while(n--){
  //   int op, x; cin>>op;

  //   if(op==1){ // insert
  //     cin>>x;
  //     cout<<veb->insert(x);
  //   }
  //   else if(op==2){ // remove
  //     cin>>x;
  //     cout<<veb->remove(x);
  //   }
  //   else if(op==3){ // member
  //     cin>>x;
  //     cout<<veb->member(x);
  //   }
  //   else if(op==4){ // successor
  //     cin>>x;
  //     cout<<veb->successor(x);
  //   }
  //   else if(op==5){ // predecessor
  //     cin>>x;
  //     cout<<veb->predecessor(x);
  //   }
  //   else if(op==6){// minimum
  //     cout<<veb->minimum();
  //   } 
  //   else if(op==7){ // maximum
  //     cout<<veb->maximum();
  //   }
  //   else if(op==8){ // extract min
  //     cout<<veb->extract_min();
  //   }

  //   cout<<endl;
  // }
}