#include <bits/stdc++.h>
using namespace std;

struct Row
{
    int start_job;
    int time;
    int next_job;
    Row(int a, int b, int c) : start_job(a), time(b), next_job(c)
    {}
};

enum class Status {visited=-1, unvisited=-2};

vector<Status> dfs_num;
vector<int> ts;

unordered_map<int,vector<int>> AL;
unordered_map<int,int> times;

void topsort(int u) {
    dfs_num[u] = Status::visited;
    for (auto &v : AL[u]) {
        if (dfs_num[v] == Status::unvisited) {
            topsort(v);
        }
    }
    ts.push_back(u);
}

int main()
{

    vector<Row> rows;

    int max_job =0;
    while (true) {
        int a, b, c;
        if (fscanf(stdin, "%d,%d,%d", &a,&b,&c) == EOF) break;
        if (a>max_job) max_job = a;
        if (b>max_job) max_job = b;
        rows.emplace_back(a,b,c);
    }
    
    // compute Adjecency List and time map
    for (const auto& row : rows) {
        AL[row.start_job].push_back(row.next_job);
        times[row.start_job] = row.time;
    }

    
    // create top-sort of all jobs
    dfs_num.assign(max_job, Status::unvisited);
    ts.clear();
    for (int u=0; u<max_job; ++u) {
        if (dfs_num[u] == Status::unvisited) {
            topsort(u);
        }
    }
    reverse(ts.begin(), ts.end());

    vector<int> chain_times;
    vector<int> chain_lengths;
    // reset state array
    dfs_num.assign(max_job, Status::unvisited);
    // chase down all chains
    for (int u=0; u<rows.size(); ++u) {
        if (dfs_num[u] == Status::unvisited) {
            // chain has started
            int i = u;
            int len = 0;
            int t = 0;
            while(true) {
                cout << "i=" << i << endl;
                dfs_num[i] = Status::visited;
                t += times[i];
                len += 1;
                //assert(AL[i].size() <= 1);
                const auto& it = AL.find(i);
                
                if (it != AL.end()) {      
                    cout << it->second.size() << endl;
                    if (it->second.size() != 1) break;
                    i = it->second[0];
                } else {
                    break;
                }                
            }
            cout << "recorded chain"<< endl;
            chain_times.push_back(t);
            chain_lengths.push_back(len);
        }
    }

    for (int i=0; i<chain_times.size(); i++) {
        cout << "result-" << i << ":" << 1.*chain_times[i] / chain_lengths[i] << " len= " << chain_lengths[i] << endl;
    }




    return 0;    
}