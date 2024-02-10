#include <bits/stdc++.h>
#include "spp/common.h"
#define _ ios_base::sync_with_stdio(false); cin.tie(0);
#define endl '\n'
#define all(x) x.begin(), x.end()
typedef long long ll;

using namespace std;
using namespace spp;

void get_orders(auto &adj, auto &vis, auto &pos_order, vertex_t u) {
    for(vertex_t v : adj[u]) {
        if(!vis[v]){
            get_orders(adj, vis, pos_order, v);
        }
    }
    pos_order.push_back(u);
}

void rauction(const auto &fs, auto &tr, auto &dr, auto &pr, vertex_t s, weight_t c) {
    const vertex_t n = fs.size();

    // preliminar 1
    vector<ll> price(n), w(n);
    vector<dist_t> ds(n, oo);
    vector<vertex_t> ps(n, NIL_VERTEX);
    vector<bool> vis(n);

    vector<ll> best_bid(n);
    vector<vector<tuple<ll, ll, ll>>> bid(n); // ps + w
    pq_t q(3*c,n);
    
    auto create_fs_bids = [&](vertex_t i) {
        for(auto [j, c] : fs[i]) {
            if(!vis[j]) {
                bid[i].emplace_back(c + price[j], j, c);
            }
        }
        sort(all(bid[i]));
        price[i] = (bid[i].size() ? get<0>(bid[i][0]) : oo);
    };

    auto erase_bs = [&](vertex_t i) {
        vis[i] = true;
    };
    auto update_best_bid = [&](ll i) {
        for(ll &it = best_bid[i]; it < bid[i].size(); it++) {
            ll j = get<1>(bid[i][it]);
            if(!vis[j]) {
                return;
            }
        }
    };
    auto has_child = [&](ll i) {
        update_best_bid(i);
        return best_bid[i] < bid[i].size();
    };
    
    auto add_subtree_to_answer = [&](vertex_t root) {

        vector<vertex_t> pos_order;
        get_orders(tr, vis, pos_order, root);
        pos_order.pop_back(); // no root
        
        for(vertex_t i : pos_order) {
            erase_bs(i);
        }

        for(vertex_t i : pos_order) {
            ds[i] = ds[root] + (dr[i] - dr[root]);
            ps[i] = pr[i];
            create_fs_bids(i);
            w[i] = w[root] + price[i];
            if(has_child(i)) {
                q.insert(w[i],i);
            }
        }

        if(has_child(root)) {
            q.insert(w[root],root);
        }
    };
    
    ds[s] = 0; ps[s] = NIL_VERTEX;
    create_fs_bids(s);
    w[s] = price[s];
    erase_bs(s);
    add_subtree_to_answer(s);

    while(q.size()) {
        vertex_t i = q.extract_min_data();
        if(!has_child(i) || get<0>(bid[i][best_bid[i]]) >= oo) { // (a)
            price[i] = w[i] = oo;
            continue;
        }
        
        const auto &[mn_bid, j, cij] = bid[i][best_bid[i]];
        if(price[i] < mn_bid) { // (b)
            ll old_price = price[i];
            price[i] = mn_bid;
            w[i] = w[i] + price[i] - old_price;
        } else { // (c)
            ps[j] = i;
            ds[j] = ds[i] + cij - (dr[i] - dr[j]);

            erase_bs(j);
            create_fs_bids(j);
            w[j] = w[i] + price[j];
            add_subtree_to_answer(j);
        }
        q.insert(w[i],i);
    }
    swap(ds, dr);
    swap(ps, pr);
}

void init_graph(const auto &adj, const auto &p, auto &d, auto &fs, auto &tr) {
    const vertex_t n = adj.size();
    for(vertex_t i = 0; i < n; i++) {
        if(p[i] != -1) tr[p[i]].push_back(i);
        for(auto [j, w] : adj[i]) {
            fs[i].emplace_back(j, w + (d[i] - d[j]));
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
        init_graph(adj, p, d, fs, tr);

        timer otimer;
        rauction(fs, tr, d, p, s, c);

        print_output(reader.get("type"), d, p, otimer);
    }
    return 0;
}