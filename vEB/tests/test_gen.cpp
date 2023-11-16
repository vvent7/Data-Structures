#include <iostream>
#include <fstream>
#include <cstdlib>
#include <set>
#include <random>
#include <cstring>
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
  uniform_int_distribution<int> uint_dist(l,r);
  return uint_dist(rng);
}

bool rand_bool(){
  uniform_int_distribution<int> uint_dist(0,1);
  return uint_dist(rng);
}

//==================================================
const int MIN_OP=1, MAX_OP=8;

int get_random(set<int> &st){
  int x = rand_int(0, st.size()-1);
  auto it = st.begin();
  while(x--) it++;
  return *it;
}

void gen_veb_test(int u, int n, string &filepathIn, string &filepathSol){
  set<int> st;

  ofstream input, sol;
  input.open(filepathIn);
  sol.open(filepathSol);
  
  rand_init();
  // cout<<"coroilho!!!\n";
  input<<u<<" "<<n<<endl; //first line
  int insTimes = n/20; //at least 5% of insertions
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
    else if(op==3){ // member
      int x=rand_int(0,u-1);
      auto it = st.find(x);
      input<<" "<<x;
      sol<<(it!=st.end());
    }
    else if(op==4){ // successor
      int x=rand_int(0,u-1);
      auto it = st.upper_bound(x);
      input<<" "<<x;
      sol<<(it!=st.end() ? *it : -1);
    }
    else if(op==5){ // predecessor
      int x=rand_int(0,u-1);
      auto it = st.lower_bound(x);
      input<<" "<<x;
      sol<<(it!=st.begin() ? *(--it) : -1);
    }
    else if(op==6){ // minimum
      sol<<(st.size() ? *st.begin() : -1);
    }
    else if(op==7){ // maximum
      sol<<(st.size() ? *st.rbegin() : -1);
    }
    else if(op==8){ // extract min
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

int main(int argc, char** argv){
  if(argc<5){
    // UNIVERSE SIZE, NUMBER OF QUERIES, INPUT filepath, SOLUTION filepath
    cout<<"Usage: "<<argv[0]<<" <universe size> <number of queries> <input filepath> <solution filepath>\n";
    return 1;
  }

  int u = atoi(argv[1]), n = atoi(argv[2]);
  string filepathIn = argv[3], filepathSol = argv[4];
  cout<<u<<" "<<n<<" "<<filepathIn<<" "<<filepathSol<<endl;
  gen_veb_test(u, n, filepathIn, filepathSol);

  return 0;
}