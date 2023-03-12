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

struct Path
{
    uint16_t first;
    uint16_t last;
    // set<int> path_nodes;
    unordered_set<uint16_t> path_nodes;
    // Path(const Path& o)
    // : first(o.first), last(o.last), path_nodes(o.path_nodes)
    // {
    // }
    size_t _hash;
    Path(uint16_t node)
    {
        first = node;
        last = node;
        // first = node;
        path_nodes.insert(node);
        _hash = node + 1;
    }
    Path(const Path &parent, uint16_t node)
        : path_nodes(parent.path_nodes)
    {
        first = parent.first;
        last = node;
        path_nodes.insert(node);
        _hash = parent._hash * (node + 1);
    }

    bool operator==(const Path &o) const
    {
        return o.last == last /* && o.first == first */ && o.path_nodes == path_nodes;
        // return o.path_nodes == path_nodes;
        // return o.path_nodes == path_nodes;
    }
    // bool operator<(const Path &o) const
    // {
    //     return last < o.last || (last == o.last && path_nodes < o.path_nodes); //
    //     // return o.path_nodes == path_nodes;
    // }
};

ostream &operator<<(ostream &os, const Path &p)
{
    // os << p.first << "," << p.last << " | ";
    os << p.last << " | ";
    for (int n : p.path_nodes)
    {
        os << n << " ";
    }
    return os;
}

namespace std
{
    template <>
    struct hash<Path>
    {
        size_t operator()(Path const &p) const noexcept
        {
            return static_cast<size_t>(p._hash) * p.last;
            // size_t i = 1;
            // for (auto n : p.path_nodes)
            //     i *= n;
            // i *= p.last;
            // //i *= p.first;
            // return i;
        }
    };
}

void extend(const Path &path, const vector<unordered_set<uint16_t>> &AL,
            vector<Path> &agenda)
{
    // if (path.path_nodes.size()>1 && last_nodes_in_agenda.find(path.first) != last_nodes_in_agenda.end())
    //     return;
    for (auto cn : AL[path.last])
    {
        if (path.path_nodes.find(cn) != path.path_nodes.end())
        {
            continue;
        }
        Path child(path, cn);

        // cout << " ... child:" << child << endl;
        // if (history.find(child) == history.end())
        // {
        // history.insert(child);
        agenda.push_back(std::move(child));
        // }
    }
}

int brute_force(const unordered_set<uint16_t> &node_set, const vector<unordered_set<uint16_t>> &AL)
{
    //
    //
    // cout << "!!!!!!!!! B R U T E     F O R C E !!!!!!!! (" << node_set.size() << ")" << endl;

    // 1. we know all nodes are connected
    // there's no point starting in the middle

    vector<uint16_t> nodes(node_set.begin(), node_set.end());
    sort(nodes.begin(), nodes.end(), [&](uint16_t a, uint16_t b) -> bool
         { return AL[a].size() < AL[b].size(); });
    // unordered_set<Path> history;

    // size_t min_degree = node_set.size();
    // for (auto n : nodes) {
    //     min_degree = min(min_degree, AL[n].size());
    //     if (min_degree == 1) {
    //         break;
    //     }
    // }
    // cout << "MIN_DEGEE = " << min_degree << endl;

    vector<Path> agenda;
    // int added=0;
    // int skipped=0;
    for (auto n : nodes)
    {
        // if (AL[n].size() == min_degree) {
        // history.emplace(n);
        agenda.emplace_back(n);
        // added++;
        // } else {
        //     // skipped++;
        // }
    }
    // cout << "Added: " << added << ", skipped: " << skipped << " AS: " << agenda.size() << endl;
    int node_set_size = node_set.size();
    int max_size = 0;
    while (!agenda.empty())
    {

        // cout << "** AGENDA **" << endl;
        // cout << max_size << endl;
        //  for (const Path &ai : agenda)
        //  {
        //      cout << ai << endl;
        //  }
        //  cout << "************" << endl;
        Path current = agenda.back();
        int cs = current.path_nodes.size();
        if (cs > max_size)
            max_size = cs;
        if (max_size == node_set_size)
            break;
        agenda.pop_back();
        extend(current, AL, agenda);
    }
    return max_size;
}

// void fill_pred(const vector<unordered_set<uint16_t>>& AL, vector<unordered_set<uint16_t>>& PL) {

//     for (uint16_t i=0; i<AL.size(); i++) {
//         const unordered_set<uint16_t>& followers_of_i = AL[i];
//         for (auto f : followers_of_i) {
//             PL[f].insert(i);
//         }
//     }

// }

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

    // // List of predecessors
    // vector<unordered_set<uint16_t>> PL(array.size());
    // //fill_pred(AL, PL);

    vector<unordered_set<uint16_t>> ccs(array.size());

    int num_ccs = 0;

    int max_num_visited = 0;
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
        //cout << "CC-Size=" << cc_it->size() << endl;
        if (cc_it->size() > max_num_visited)
        {
            max_num_visited = max(max_num_visited, brute_force(*cc_it, AL));
        }
        else
        {
          //  cout << "Break\n";
            break;
        }
    }
    cout << max_num_visited;
    return 0;
}