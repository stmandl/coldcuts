#include<bits/stdc++.h>
using namespace std;

using Adj = unordered_map<int, vector<int>>;
using Graph = Adj;

void insert_edge_ab(Graph&g, int a, int b) {
    vector<int>& n = g[a];
    auto it = find(n.begin(), n.end(), b);
    if (it == n.end()) {
        n.push_back(b);
    }
}

Graph make_graph(const Adj& adj) {
    Graph g;
    for (const auto [from, to] : adj) {
        for (const int t : to) {
            insert_edge_ab(g, from, t);
        }
    }
    return g;
}


namespace std {
    template<>
    struct hash<pair<int, int>> {
        size_t operator()(const pair<int, int> p) const {
            return static_cast<size_t>(p.first+37*p.second);
        }
    };
}

void print(Graph& g) {
    unordered_set<pair<int,int>> printed;
    for (const auto [node, neigh] : g) {
        for (auto n :  neigh) {
            //assert (find(g[n].begin(), g[n].end(), node) != g[n].end());            
            if (printed.find({n,node}) == printed.end()) {
                cout << node << " -- " << n << endl;
                printed.insert(make_pair(n, node));
                printed.insert(make_pair(node, n));
            }
        }
    }
}

int main()
{
    Graph g;
    g[1] = {2,3};
    g[2] = {4};
    g[3] = {};
    print(g);
}