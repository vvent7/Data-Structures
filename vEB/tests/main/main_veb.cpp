#include <iostream>
#include "veb/veb.h"
#define _ ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define endl '\n'
using namespace std;

int main(){_
  int u, n;
  cin>>u>>n;
  
  Veb *veb = new Veb(u);

  while(n--){
    int op, x; cin>>op;

    if(op==1){ // insert
      cin>>x;
      cout<<veb->insert(x);
    }
    else if(op==2){ // remove
      cin>>x;
      cout<<veb->remove(x);
    }
    else if(op==3){ // member
      cin>>x;
      cout<<veb->member(x);
    }
    else if(op==4){ // successor
      cin>>x;
      cout<<veb->successor(x);
    }
    else if(op==5){ // predecessor
      cin>>x;
      cout<<veb->predecessor(x);
    }
    else if(op==6){// minimum
      cout<<veb->minimum();
    } 
    else if(op==7){ // maximum
      cout<<veb->maximum();
    }
    else if(op==8){ // extract min
      cout<<veb->extract_min();
    }

    cout<<endl;
  }
}