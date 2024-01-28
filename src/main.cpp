#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define endl '\n'
#define fi first
#define sec second
#define eb emplace_back
using namespace std;
typedef long long ll;
typedef pair<int, int> pi;
typedef pair<ll,ll> pll;
typedef pair<double,double> pdb;
typedef pair<double,int> pdbi;
typedef tuple<ll,ll,ll> t3;
typedef list<pair<int,bool>>::iterator lit;
// #include<bits/extc++.h>
// using namespace __gnu_pbds;
// typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ost;

#include "container/kdc_set.h"
#include "container/kdc_vector_unordered.h"
#include "veb/veb_data/veb_data.h"
#include "pred_list/pred_list_env.h"
#include "pred_list/pred_list_set.h"
#include "pred_list/pred_list_data.h"
#include "pred_bitset/pred_bitset_env.h"
#include "pred_bitset/pred_bitset_set.h"
#include "pred_bitset/pred_bitset_data.h"
#include "circular.h"

signed main(){_
  Circular<veb::Data<kdc_vector_unordered>> ds(10, 100);

  cout<<ds.empty()<<endl;           //1
  cout<<ds.extract_min_key()<<endl; //4294967295
  cout<<ds.insert(2,50)<<endl;      //1
  cout<<ds.insert(5,2)<<endl;       //1
  cout<<ds.insert(5,3)<<endl;       //1
  cout<<ds.insert(6,0)<<endl;       //1
  cout<<ds.insert(6,30)<<endl;      //1
  cout<<ds.insert(7,50)<<endl;      //0
  cout<<ds.insert(8,20)<<endl;     //1
  cout<<ds.empty()<<endl;           //0

  cout<<ds.minimum().first<<" "<<ds.minimum().second<<endl; //2 50
  cout<<ds.maximum().first<<" "<<ds.maximum().second<<endl; //8 20
  cout<<ds.successor_key(4)<<endl;   //5
  cout<<ds.predecessor_key(4)<<endl; //2
  
  cout<<ds.remove_data(50)<<endl;     //1
  cout<<ds.remove_data(50)<<endl;     //0
  cout<<ds.remove_key(5)<<endl;       //2
  cout<<ds.remove_key(5)<<endl;       //0
  cout<<ds.decrease_key(20, 5)<<endl; //1
  
  cout<<ds.minimum().first<<" "<<ds.minimum().second<<endl; //5 20
  cout<<ds.maximum().first<<" "<<ds.maximum().second<<endl; //6 0
  cout<<ds.successor_key(4)<<endl;   //5
  cout<<ds.predecessor_key(4)<<endl; //4294967295

  // 5 20, 6 30, 6 0
  auto x = ds.extract_min();
  cout<<x.fi<<" "<<x.sec<<endl; //5 20 (last = 5)

  cout<<ds.insert(ds.toBitKey(5+9), 2)<<endl;  //1
  cout<<ds.insert(ds.toBitKey(5+6), 99)<<endl; //1
  cout<<ds.insert(ds.toBitKey(5+7), 99)<<endl; //0
  
  while(!ds.empty()){
    auto x = ds.extract_min();
    cout<<x.fi<<" "<<x.sec<<endl; //6 30, 6 0, 0 99, 3 2
  }
  cout<<ds.extract_min_data()<<endl; //4294967295
  cout<<ds.empty()<<endl; // 1
}

/* CIRCULAR DATA
  Circular<veb::Data<kdc_vector_unordered>> ds(10, 100);

  cout<<ds.empty()<<endl;           //1
  cout<<ds.extract_min_key()<<endl; //4294967295
  cout<<ds.insert(2,50)<<endl;      //1
  cout<<ds.insert(5,2)<<endl;       //1
  cout<<ds.insert(5,3)<<endl;       //1
  cout<<ds.insert(6,0)<<endl;       //1
  cout<<ds.insert(6,30)<<endl;      //1
  cout<<ds.insert(7,50)<<endl;      //0
  cout<<ds.insert(8,20)<<endl;     //1
  cout<<ds.empty()<<endl;           //0

  cout<<ds.minimum().first<<" "<<ds.minimum().second<<endl; //2 50
  cout<<ds.maximum().first<<" "<<ds.maximum().second<<endl; //8 20
  cout<<ds.successor_key(4)<<endl;   //5
  cout<<ds.predecessor_key(4)<<endl; //2
  
  cout<<ds.remove_data(50)<<endl;     //1
  cout<<ds.remove_data(50)<<endl;     //0
  cout<<ds.remove_key(5)<<endl;       //2
  cout<<ds.remove_key(5)<<endl;       //0
  cout<<ds.decrease_key(20, 5)<<endl; //1
  
  cout<<ds.minimum().first<<" "<<ds.minimum().second<<endl; //5 20
  cout<<ds.maximum().first<<" "<<ds.maximum().second<<endl; //6 0
  cout<<ds.successor_key(4)<<endl;   //5
  cout<<ds.predecessor_key(4)<<endl; //4294967295

  // 5 20, 6 30, 6 0
  auto x = ds.extract_min();
  cout<<x.fi<<" "<<x.sec<<endl; //5 20 (last = 5)

  cout<<ds.insert(ds.toBitKey(5+9), 2)<<endl;  //1
  cout<<ds.insert(ds.toBitKey(5+6), 99)<<endl; //1
  cout<<ds.insert(ds.toBitKey(5+7), 99)<<endl; //0
  
  while(!ds.empty()){
    auto x = ds.extract_min();
    cout<<x.fi<<" "<<x.sec<<endl; //6 30, 6 0, 0 99, 3 2
  }
  cout<<ds.extract_min_data()<<endl; //4294967295
  cout<<ds.empty()<<endl; // 1
*/

/*  DATA
  pred_bitset::Data<kdc_vector_unordered> ds(100, 100);

  cout<<ds.empty()<<endl;           //1
  cout<<ds.extract_min_key()<<endl; //4294967295
  cout<<ds.insert(2,50)<<endl;      //1
  cout<<ds.insert(5,2)<<endl;       //1
  cout<<ds.insert(5,3)<<endl;       //1
  cout<<ds.insert(6,0)<<endl;       //1
  cout<<ds.insert(6,30)<<endl;      //1
  cout<<ds.insert(7,50)<<endl;      //0
  cout<<ds.insert(8, 20)<<endl;     //1
  cout<<ds.empty()<<endl;           //0


  cout<<ds.minimum().first<<" "<<ds.minimum().second<<endl; //2 50
  cout<<ds.maximum().first<<" "<<ds.maximum().second<<endl; //8 20
  cout<<ds.successor_key(4)<<endl;   //5
  cout<<ds.predecessor_key(4)<<endl; //2
  
  cout<<ds.remove_data(50)<<endl;     //1
  cout<<ds.remove_data(50)<<endl;     //0
  cout<<ds.remove_key(5)<<endl;       //2
  cout<<ds.remove_key(5)<<endl;       //0
  cout<<ds.decrease_key(20, 5)<<endl; //1
  
  cout<<ds.minimum().first<<" "<<ds.minimum().second<<endl; //5 20
  cout<<ds.maximum().first<<" "<<ds.maximum().second<<endl; //6 0
  cout<<ds.successor_key(4)<<endl;   //5
  cout<<ds.predecessor_key(4)<<endl; //4294967295

  while(!ds.empty()){
    auto x = ds.extract_min();
    cout<<x.fi<<" "<<x.sec<<endl; //5 20, 6 30, 6 0
  }
  cout<<ds.extract_min_data()<<endl; //4294967295
  cout<<ds.empty()<<endl; // 1
*/

/* set
  pred_list::PredListSet st;

  cout<<st.empty()<<endl;   //1
  cout<<st.insert(5)<<endl; //1
  cout<<st.insert(0)<<endl; //1
  cout<<st.insert(5)<<endl; //0
  cout<<st.insert(2)<<endl; //1
  cout<<st.empty()<<endl;   //0
  cout<<st.minimum()<<endl; //0
  cout<<st.maximum()<<endl; //5
  cout<<st.successor(1)<<endl;   //2
  cout<<st.predecessor(1)<<endl; //0
  cout<<st.extract_min()<<endl; //0
  cout<<st.minimum()<<endl; //2
  cout<<st.maximum()<<endl; //5
  cout<<st.successor(1)<<endl;   //2
  cout<<st.predecessor(1)<<endl; //NIL
  cout<<st.size()<<endl; //2
*/