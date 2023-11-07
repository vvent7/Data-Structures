#include <iostream>
#include <fstream>
#include <cstdlib>
#include <set>
#include <random>
using namespace std;

//======================RANDOM======================
typedef std::mt19937 MyRNG; //type of engine
uint32_t seed_val;  //seed
MyRNG rng; //engine

void rand_init(){
  seed_val = std::random_device()();
  rng.seed(seed_val);
}

int rand_int(int l, int r){
  int range = r-l;
  uniform_int_distribution<int> uint_dist(0,range);
  return l + uint_dist(rng);
}

//==================================================

const int MIN_OP=1, MAX_OP=9;


void gen_veb_test(int u, int n){
  set<int> st;

  ofstream input, sol;
  input.open ("in");
  sol.open ("sol");
  
  rand_init();
  
  input<<u<<" "<<n<<endl; //first line
  int insTimes = n/3;
  while(n--){
    int op = insTimes
      ? (insTimes--, 1)
      : rand_int(MIN_OP,MAX_OP);

    input<<op; //op

    if(op==1){ // insert
      int x=rand_int(0,u-1);
      input<<" "<<x;
      sol<<st.insert(x).second;
    }
    else if(op==2){ // remove
      int x=rand_int(0,u-1);
      input<<" "<<x;
      sol<<st.erase(x);
    }
    else if(op==3){ // get size
      sol<<st.size();
    }
    else if(op==4){ // member
      int x=rand_int(0,u-1);
      auto it = st.find(x);
      input<<" "<<x;
      sol<<(it!=st.end());
    }
    else if(op==5){ // successor
      int x=rand_int(0,u-1);
      auto it = st.upper_bound(x);
      input<<" "<<x;
      sol<<(it!=st.end() ? *it : -1);
    }
    else if(op==6){ // predecessor
      int x=rand_int(0,u-1);
      auto it = st.lower_bound(x);
      input<<" "<<x;
      sol<<(it!=st.begin() ? *(--it) : -1);
    }
    else if(op==7){ // minimum
      sol<<(st.size() ? *st.begin() : -1);
    }
    else if(op==8){ // maximum
      sol<<(st.size() ? *st.rbegin() : -1);
    }
    else if(op==9){ // extract min
      if(st.size()){
        int x = *st.begin();
        st.erase(st.begin());
        sol<<x;
      }
      else sol<<-1;
    }

    input<<endl;
    sol<<endl;
  }
}

void gen_veb_multi_test(int u, int n){
  //on hold...
}

int main(int argc, char** argv){
  if(argc<3){
    cout<<"Usage: "<<argv[0]<<" <universe size> <number of queries>\n";
    return 1;
  }

  int u = atoi(argv[1]), n = atoi(argv[2]);
  gen_veb_test(u,n);

  return 0;
}