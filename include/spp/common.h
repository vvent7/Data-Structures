#ifndef COMMON_H
#define COMMON_H

#include <map>     //map
#include <list>    //list
#include <vector>  //vector
#include <utility> //pair
#include <string>  //string
#include <tuple>   //tuple
#include <chrono>  //chrono
#include "spp_env.h"
#include "pqueues.h"

namespace spp {
  using namespace std;
  
  //===================TYPES===================
  using pq_t = pqueue_bintree_t;
  using vw_t = pair<vertex_t, weight_t>;
  using list_vw_t = list<vw_t>;
  using graph_t = vector<list_vw_t>;
  //===========================================

  //===================CONFIG===================
  class cfg_reader {
  public:
    cfg_reader();
    string get(string s);
  private:
    map<string, string> res;
  };
  //============================================

  //===================GRAPH READER===================
  //{adj, n (vertexes), m(edges), c(maxWeight)}
  tuple<graph_t, vertex_t, edge_t, weight_t> graph_reader(string path);
  //==================================================

  //=======================TIMER=======================
  class timer {
  public:
    timer();
    void restart();
    double elapsed();
  private:
    chrono::_V2::system_clock::time_point begin;
  };
  //==================================================

  //=================DIJKSTRA=================
  void init_dijkstra(vector<dist_t> &d, vector<vertex_t> &p, pq_t &q, const vertex_t n, const vertex_t s);
  void dijkstra(const graph_t &adj, vector<dist_t> &d, vector<vertex_t> &p, pq_t &q);
  //==========================================

  //===============CHECKSUM AND OUTPUT================
  long long check_sum(auto &v);

  void print_output(string type, vector<dist_t> &d, vector<vertex_t> &p, timer &otimer);
  //==================================================
}


#endif