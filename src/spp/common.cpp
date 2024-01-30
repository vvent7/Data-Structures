#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
using namespace std;

#include <iostream>
#include <map>     //map
#include <list>    //list
#include <vector>  //vector
#include <utility> //pair
#include <string>  //string
#include <tuple>   //tuple
#include <chrono>  //chrono
#include "spp/spp_env.h"
#include "spp/pqueues.h"
#include "spp/common.h"

namespace spp{

  //===================CONFIG===================
  cfg_reader::cfg_reader() {
    string config_path = getenv("RSPP_ROOT");
    config_path += "config";
    cout<<config_path<<endl;

    ifstream in(config_path);
    string line;
    while(getline(in, line)) {
      istringstream linestream(line);
      string key, value;
      getline(linestream, key, '=');
      getline(linestream, value);
      res[key] = value;
    }
  }
  string cfg_reader::get(string s) {
    return res[s];
  }
  //============================================

  //===================GRAPH READER===================
  void graph_reader_r(string &path, graph_t &adj, vertex_t &n, edge_t &m, weight_t &c){
    string line, tmp;
    ifstream in(path);

    while(getline(in, line)) {
      stringstream ss(line);
      if(line[0] == 'p') {
        ss >> tmp >> tmp >> n >> m;
        adj.resize(n+1); // n++;
      } else if(line[0] == 'a') {
        vertex_t a, b;
        weight_t w;
        ss >> tmp >> a >> b >> w;
        adj[a].emplace_back(b, w);
        
        if(w > c) c = w; // c = max(c, w);
      }
    }
  }

  void graph_reader_t(string &path, graph_t &adj, vertex_t &n, edge_t &m, weight_t &c){
    string line, tmp;
    ifstream in(path);

    while(getline(in, line)) {
      stringstream ss(line);
      if(n != NIL_VERTEX) {
        vertex_t a, b;
        weight_t w;
        ss >> a;
        
        if(a == NIL_VERTEX) break; // if(a == -1) break;

        ss >> b >> w;
        adj[a].emplace_back(b, w);
        
        if(w > c) c = w; // c = max(c, w);
        ++m;
      } else {
        ss >> n;
        adj.resize(n+1); // n++;
      }
    }
  }

  void graph_reader_n(string &path, graph_t &adj, vertex_t &n, edge_t &m, weight_t &c){
    string line, tmp;
    ifstream in(path);

    while(getline(in, line)) {
      stringstream ss(line);
      if(n != NIL_VERTEX) {
        vertex_t a, b;
        weight_t w;
        ss >> a;
        if(a == 0) break;

        ss >> b >> tmp >> w;
        adj[a].emplace_back(b, w);

        if(w > c) c = w; // c = max(c, w);
        ++m;
      } else {
        ss >> n;
        adj.resize(n+1); // n++;
      }
    }
  }

  //{adj, c(maxWeight), n (vertexes), m (edges)}
  tuple<graph_t, vertex_t, edge_t, weight_t> graph_reader(string path) {
    tuple<graph_t, vertex_t, edge_t, weight_t> res;
    auto &[adj, n, m, c] = res;
    n = NIL_VERTEX; //number of vertexes
    m = 0; //number of edges
    c = 0; //max weight
    
    switch(path.back()){
      case 'r':
        graph_reader_r(path, adj, n, m, c); break;
      case 't':
        graph_reader_t(path, adj, n, m, c); break;
      case 'n':
        graph_reader_n(path, adj, n, m, c); break;
      default: break;
    }

    return res;
  }
  //==================================================

  //=================DIJKSTRA=================
  void init_dijkstra(vector<dist_t> &d, vector<vertex_t> &p, pq_t &q, const vertex_t n, const vertex_t s) {
    d = vector<dist_t>(n+1, oo);
    p = vector<vertex_t>(n+1, NIL_VERTEX);
    d[s] = 0;
    q.insert(0, s);
  }

  void dijkstra(const graph_t &adj, vector<dist_t> &d, vector<vertex_t> &p, pq_t &q) {
    while(!q.empty()) {
      auto u = q.extract_min_data(); //closest vertex(minimum data)
      for(auto [v, w] : adj[u]) {
        dist_t dVreal = d[u] + w;
        if(d[v] > dVreal) {
          if(d[v] == oo) q.insert(dVreal, v);
          else q.decrease_key(dVreal, v);
          p[v] = u;
          d[v] = dVreal;
        }
      }
    }
  };
  //==========================================

  //=======================TIMER=======================
  timer::timer() {
    begin = chrono::high_resolution_clock::now();
  }
  void timer::restart() {
    begin = chrono::high_resolution_clock::now();
  }
  double timer::elapsed() {
    auto end = chrono::high_resolution_clock::now();
    return chrono::duration_cast<chrono::microseconds>(end - begin).count() / double(1000); //milliseconds
  }
  //==================================================


  //===============CHECKSUM AND OUTPUT================
  long long check_sum(auto &v) {
      long long res = 0;
      for(auto x : v) {
          res += x;
      }
      return res;
  }

  void print_output(string type, vector<dist_t> &d, vector<vertex_t> &p, timer &otimer) {
    cout << fixed << setprecision(3);
    if(type.find("main_time") != string::npos) {
      cout << otimer.elapsed() << endl;
    }
    if(type.find("check_sum") != string::npos){
      cout << check_sum(d) << endl;
    }
  }
  //==================================================
}

