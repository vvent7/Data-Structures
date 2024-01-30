#include<bits/stdc++.h>

using namespace std;

int main(){
  string s;
  cout<<"instâncias,dijkstra,rdijkstra,rdijkstra-v2,rauction,rauction-v2";
  while(getline(cin,s)){
    if(s[0]!='/'){
        if(!isalpha(s.back())) cout<<s<<",";
        else cout<<endl<<s<<",";
    }
  }
}