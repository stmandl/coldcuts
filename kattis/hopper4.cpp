#include <bits/stdc++.h>
using namespace std;

enum
{
    UNVISITED = -1,
    VISITED = -2
};

void add_neighbours(const int u, unordered_set<uint16_t> &reachable, const vector<int> &array, int max_dist, int max_diff)
{
    int asize = array.size();
    max_dist = max_dist % asize;
    //  explore the range around last_position
    int current_element = array[u];
    // unordered_set<int> seen_positions;
    for (int pos = max(0, u - max_dist); pos <= min(u + max_dist, asize - 1); pos++)
    {
        if (pos == u)
        {
            continue;
        }
        // if (seen_positions.find(pos) == seen_positions.end())
        // {
        // seen_positions.insert(pos);
        if (abs(current_element - array[pos]) <= max_diff)
        {
            //      cout << " " << pos;
            reachable.insert(pos);
        }
        // }
    }
    // cout << endl;
}

void dfs(int u, vector<int> &dfs_num, const vector<unordered_set<uint16_t>> &AL, unordered_set<uint16_t> &cc /*, unordered_set<int>& visisted*/)
{
    dfs_num[u] = VISITED;
    cc.insert(u);
    for (auto v : AL[u])
    {
        if (dfs_num[v] == UNVISITED /* && visisted.find(v) == visisted.end() */)
        {
            dfs(v, dfs_num, AL, cc /*, visisted */);
        }
    }
}

bitset<10000> elems;
uint16_t max_depth;
// map<pair<set<uint16_t>, uint16_t>, uint16_t> depth_cache;
unordered_set<uint16_t> finish_nodes;

inline uint16_t brute_force_rec(uint16_t n, const vector<unordered_set<uint16_t>> &AL, uint16_t depth)
{
    if (AL[n].size() == 1)
    {
        finish_nodes.insert(n);
    }
    uint16_t best_depth = depth;    
    if (best_depth < max_depth)
    {
        bool hit_end = true;
        for (uint16_t c : AL[n])
        {
            if (elems.test(c))
                continue;
            hit_end=false;
            uint16_t dc = -1;
            // auto cr = depth_cache.find(make_pair(elems,c));
            // if (cr != depth_cache.end()) {
            //     dc = cr->second;
            // } else {
            elems.set(c);
            dc = brute_force_rec(c, AL, depth + 1);
            elems.reset(c);
            // depth_cache.insert(make_pair(make_pair(elems,c), dc));
            // }
            best_depth = max(best_depth, dc);
            if (best_depth == max_depth)
                break;
        }
        if (hit_end) {
            //cout << "Hit end at depth " << depth  << " / " << max_depth << endl;
        }
    }
    return best_depth;
}

inline uint16_t brute_force(const unordered_set<uint16_t> &node_set, vector<unordered_set<uint16_t>> &AL)
{
    vector<uint16_t> nodes(node_set.begin(), node_set.end());
    sort(nodes.begin(), nodes.end(), [&](uint16_t a, uint16_t b) -> bool
        { return AL[a].size() > AL[b].size(); });

    uint16_t max_size = 0;
    max_depth = node_set.size();
    elems.reset();
    finish_nodes.clear();
    
    for (auto n : nodes)
    {
        if (finish_nodes.find(n) != finish_nodes.end())
            continue;
        elems.set(n);
        max_size = max(max_size, brute_force_rec(n, AL, 1));
        elems.reset(n);
        if (max_size == max_depth)
            break;
    }
    return max_size;
}

// Idee: Graph ausdünnen: Cliquen (oder ähnliches) eventuell auf einen einzigen Knoten minimieren?
// 

int main()
{
    int n, D, M;
    cin >> n;
    cin >> D;
    cin >> M;

    vector<int> array;
    array.reserve(n);
    for (int i = 0; i < n; i++)
    {
        int element;
        cin >> element;
        array.push_back(element);
    }

    // create Adjacency list
    vector<unordered_set<uint16_t>> AL(array.size());

    vector<int> dfs_num;
    dfs_num.assign(array.size(), UNVISITED);

    for (int u = 0; u < array.size(); ++u)
    {
        add_neighbours(u, AL[u], array, D, M);
    }

    vector<unordered_set<uint16_t>> ccs(array.size());

    int num_ccs = 0;

    uint16_t max_num_visited = 0;
    for (int u = 0; u < array.size(); ++u)
    {
        if (dfs_num[u] == UNVISITED)
        {
            // unordered_set<uint16_t> cc;
            dfs(u, dfs_num, AL, ccs[num_ccs++] /*, visited*/);
            // cout << "XX " << u << " CC size=" << cc.size() << endl;
        }
    }
    sort(ccs.begin(), ccs.begin() + num_ccs, [](const unordered_set<uint16_t> &a, const unordered_set<uint16_t> &b) -> bool
         { return a.size() > b.size(); });
    for (auto cc_it = ccs.begin();
         cc_it != ccs.begin() + num_ccs;
         ++cc_it)
    {        
        if (cc_it->size() > max_num_visited)
        {

            max_num_visited = max(max_num_visited, brute_force(*cc_it, AL));
        }
        else
        {         
            break;
        }
    }
    cout << max_num_visited;
    return 0;
}