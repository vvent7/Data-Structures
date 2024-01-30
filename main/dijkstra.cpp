#include <bits/stdc++.h>
#include "spp/common.h"
#define _ ios_base::sync_with_stdio(false); cin.tie(0);
#define endl '\n'
#define all(x) x.begin(), x.end()
typedef long long ll;

using namespace std;
using namespace spp;

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
    
    pq_t q2(c,n);
    timer otimer;
    init_dijkstra(d, p, q2, n, s);
    dijkstra(adj, d, p, q2);

    print_output(reader.get("type"), d, p, otimer);
  }
  return 0;
}
