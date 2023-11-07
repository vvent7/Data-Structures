#include <iostream>
#include "veb_pre.h"
using namespace std;

int main(){
  int u, n;
  cin>>u>>n;

  VebPre veb(u);

  while(n--){
    int op, x; cin>>op;

    if(op==1){ // insert
      cin>>x;
      cout<<veb.insert(x);
    }
    else if(op==2){ // remove
      cin>>x;
      cout<<veb.remove(x);
    }
    else if(op==3) // get size
      cout<<veb.size();
    else if(op==4){ // member
      cin>>x;
      cout<<veb.member(x);
    }
    else if(op==5){ // successor
      cin>>x;
      cout<<veb.successor(x);
    }
    else if(op==6){ // predecessor
      cin>>x;
      cout<<veb.predecessor(x);
    }
    else if(op==7) // minimum
      cout<<veb.minimum();
    else if(op==8) // maximum
      cout<<veb.maximum();
    else if(op==9) // extract min
      cout<<veb.extract_min();

    cout<<endl;
  }

}