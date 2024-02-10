#include <bits/stdc++.h>
#include "spp/common.h"
#define _ ios_base::sync_with_stdio(false); cin.tie(0);
#define endl '\n'
#define all(x) x.begin(), x.end()
typedef long long ll;

using namespace std;
using namespace spp;

void get_post_order(auto &adj, auto &res, vertex_t u) {
  for(vertex_t v : adj[u]){
    get_post_order(adj, res, v);
  }
  res.push_back(u);
}

void rdijkstra(auto &fs, const auto &bs, auto &tr, auto &dr, auto &pr, vertex_t s, weight_t c) {
  const vertex_t n = fs.size();

  auto erase_bs = [&](vertex_t i) {
    for(auto [j, it] : bs[i]) { // j -> i
      fs[j].erase(it);
    }
  };
  
  vector<dist_t> ds(n, oo);
  vector<vertex_t> ps(n, NIL_VERTEX);

  vector<vertex_t> porder;
  get_post_order(tr, porder, s);
  
  for(vertex_t i : porder) {
      ds[i] = dr[i] - dr[s];
      ps[i] = pr[i];
      erase_bs(i);
    if(ds[i]>c) c=ds[i]; //getting biggest change
  }
  
  pq_t q(c,n); //building structure
  for(vertex_t i : porder) {
      if(!fs[i].empty()) {
          q.insert(ds[i],i);
      }
  }
  
  ps[s] = NIL_VERTEX;

  dijkstra(fs, ds, ps, q);

  dr = move(ds);
  pr = move(ps);
}

void init_graph(const auto &adj, const auto &p, auto &fs, auto &bs, auto &tr) {
    const vertex_t n = adj.size();
    for(vertex_t i = 0; i < n; i++) {
        if(p[i] != NIL_VERTEX) tr[p[i]].push_back(i);
        for(auto [j, w] : adj[i]) {
            fs[i].emplace_back(j, w);
            bs[j].emplace_back(i, --fs[i].end());
        }
    }
}

signed main() {_
  cfg_reader reader;
  string dataset_path = reader.get("dataset");
  string query_path = reader.get("query");

  auto [adj, n, m, c] = graph_reader(dataset_path);

  vector<dist_t> d;
  vector<vertex_t> p;

  auto in = ifstream(query_path);
  ll t; in >> t;
  while(t--) {
    vertex_t r, s; in >> r >> s;

    pq_t q(c,n);
    init_dijkstra(d, p, q, n, r);
    dijkstra(adj, d, p, q);

    vector<vector<vertex_t>> tr(n+1);
    graph_t fs(n+1);
    vector<vector<pair<vertex_t, list_vw_t::iterator>>> bs(n+1);
    init_graph(adj, p, fs, bs, tr);
    
    timer otimer;
    rdijkstra(fs, bs, tr, d, p, s, c);
    
    print_output(reader.get("type"), d, p, otimer);
  }
  return 0;
}