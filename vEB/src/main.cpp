#include <iostream>
#include "_veb_base.h"
#include "veb_pre.h"
#include "veb.h"
using namespace std;

int main(){
  int u, n;
  cin>>u>>n;

  _veb_base *veb = new Veb(u);

  while(n--){
    int op, x; cin>>op;

    if(op==1){ // insert
      cin>>x;
      // cout<<"inserting "<<x<<": "<<std::flush;
      
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
    else if(op==6) // minimum
      cout<<veb->minimum();
    else if(op==7) // maximum
      cout<<veb->maximum();
    else if(op==8) // extract min
      cout<<veb->extract_min();

    cout<<endl;
  }

}