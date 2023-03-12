#include <bits/stdc++.h>
using namespace std;

enum
{
    UNVISITED = -1,
    VISITED = -2
};

void add_neighbours(const int u, unordered_set<int> &reachable, const vector<int> &array, int max_dist, int max_diff)
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

void dfs(int u, vector<int> &dfs_num, const vector<unordered_set<int>> &AL, unordered_set<int> &cc /*, unordered_set<int>& visisted*/)
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
    //int first;
    int last;
    //set<int> path_nodes;
    unordered_set<int> path_nodes;
    // Path(const Path& o)
    // : first(o.first), last(o.last), path_nodes(o.path_nodes)
    // {
    // }
    size_t _hash;
    Path(int node)
    {
        last = node;
        //first = node;
        path_nodes.insert(node);
        _hash = node;
    }
    Path(const Path &parent, int node)
        : path_nodes(parent.path_nodes)
    {
        last = node;        
        path_nodes.insert(node);
        _hash = parent._hash * node;
    }

    bool operator==(const Path &o) const
    {
        return o.last == last/* && o.first == first */ && o.path_nodes == path_nodes;
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
            return p._hash * p.last;
            // size_t i = 1;
            // for (auto n : p.path_nodes)
            //     i *= n;
            // i *= p.last;
            // //i *= p.first;
            // return i;
        }
    };
}


void extend(const Path &path, vector<unordered_set<int>> &AL, vector<Path> &agenda, /*unordered_set<Path> history,*/ const vector<int> &array)
{
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

int brute_force(const unordered_set<int> &node_set, vector<unordered_set<int>> &AL, const vector<int> &array)
{
    //
    //
    // cout << "!!!!!!!!! B R U T E     F O R C E !!!!!!!! (" << node_set.size() << ")" << endl;
    vector<int> nodes(node_set.begin(), node_set.end());
    sort(nodes.begin(), nodes.end());
    //unordered_set<Path> history;
    vector<Path> agenda;
    for (auto n : nodes)
    {
        // history.emplace(n);
        agenda.emplace_back(n);
    }
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
        if (max_size == node_set.size())
            break;
        agenda.pop_back();
        extend(current, AL, agenda, /*history,*/ array);
    }
    return max_size;
}

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
    vector<unordered_set<int>> AL(array.size());

    vector<int> dfs_num;
    dfs_num.assign(array.size(), UNVISITED);

    for (int u = 0; u < array.size(); ++u)
    {
        add_neighbours(u, AL[u], array, D, M);
    }

    int max_num_visited = 0;
    for (int u = 0; u < array.size(); ++u)
    {
        if (dfs_num[u] == UNVISITED)
        {
            unordered_set<int> cc;
            dfs(u, dfs_num, AL, cc /*, visited*/);
            // cout << "XX " << u << " CC size=" << cc.size() << endl;
            if (cc.size() > max_num_visited)
            {                
                max_num_visited = max(max_num_visited, brute_force(cc, AL, array));
            }
        }
    }
    cout << max_num_visited;
    return 0;
}