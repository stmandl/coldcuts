#include <bits/stdc++.h>
using namespace std;

/*

General approach:
1. Create a topological ordering of the job ids, which guarantees that can start at
   at the beginning of the chains.
2. Walk down the chains from their starts, mark all visited nodes and gather the necessary information.
3. Format output
*/

// successor relation of jobs
unordered_map<int, int> succ;
// runtime in seconds for jobs
unordered_map<int, int> runtimes;

enum class Status
{
    visited = -1,
    unvisited = -2
};
vector<Status> node_state;
vector<int> topsort_array;

// Classic implementation of topological ordering.
// It is a little overkill for this problem
// as the chains a just linked lists, but it does the job.
void topsort(int u)
{
    node_state[u] = Status::visited;    
    auto v = succ.find(u);
    if (v != succ.end() && node_state[v->second] == Status::unvisited)
    {
        topsort(v->second);
    }
    topsort_array.push_back(u);
}

// report error and exit
void error()
{
    cout << "Malformed Input";
    exit(0);
}

// The job ids are not "dense" but in the test cases
// seem to be small enough to use simple arrays to track their state.
// Hence, we sometimes have to check if a given number is actually a valid job id.
// As all valid job id have an entry in the "seconds" map, we utilize this informatino.
inline bool isJob(int j)
{
    return j != 0 && runtimes.find(j) != runtimes.end();
}

// This structure is used to gather the necessary information about chains, when they
// are extracted.
struct ChainDesc
{
    int start_job;
    int last_job;
    int number_of_jobs;
    int runtime;
    ChainDesc(int start_job_, int last_job_, int number_of_jobs_, int runtime_)
        : start_job(start_job_), last_job(last_job_), number_of_jobs(number_of_jobs_), runtime(runtime_)
    {
    }
};

void format_seconds(int s)
{
    int hours = s / 3600;
    s -= hours * 3600;
    int minutes = s / 60;
    s -= minutes * 60;
    int seconds = s;
    cout << std::setw(2) << std::setfill('0') << hours << ":"
         << std::setw(2) << std::setfill('0') << minutes << ":"
         << std::setw(2) << std::setfill('0') << seconds;
}

int main()
{

    // skip first line
    string line;
    getline(cin, line);
    if (!cin.good())
    {
        error();
    }

    unordered_set<int> seen_successors_so_far;
    int max_job = 0;
    while (true)
    {
        int a, b, c;
        int r = fscanf(stdin, "%d,%d,%d", &a, &b, &c);
        if (r == EOF) break;
        if (r == 0) error();
        if (c != 0)
        {
            if (seen_successors_so_far.find(c) != seen_successors_so_far.end())
            {
                // there is a logical error in the data: a job cannot have 2 predecessors.
                error();
            }
            seen_successors_so_far.insert(c);
            succ[a] = c;
        }
        runtimes[a] = b;
        if (a > max_job)
            max_job = a;
        if (b > max_job)
            max_job = b;
    }

    // create a topological ordering of all jobs
    node_state.assign(max_job + 1, Status::unvisited);
    topsort_array.clear();
    for (int u = 1; u <= max_job; ++u)
    {
        if (isJob(u) && node_state[u] == Status::unvisited)
        {
            topsort(u);
        }
    }
    reverse(topsort_array.begin(), topsort_array.end());    

    // extract the chains
    vector<ChainDesc> chains;

    node_state.assign(max_job + 1, Status::unvisited);
    // chase down all chains    
    for (auto job : topsort_array)
    {
        if (node_state[job] == Status::unvisited)
        {
            // chain has started
            int current = job;
            int start = job;
            int stop = 0;
            int len = 0;
            int total_runtime = 0;
            while (true)
            {
                node_state[current] = Status::visited;
                total_runtime += runtimes[current];
                len += 1;
                if (succ[current] != 0)
                {
                    current = succ[current];
                }
                else
                {
                    stop = current;
                    break;
                }
            }
            chains.emplace_back(start, stop, len, total_runtime);
        }
    }
    auto chain_comp = [](const ChainDesc &a, const ChainDesc &b)
    {
        return a.runtime > b.runtime; // descending!
    };

    sort(chains.begin(), chains.end(), chain_comp);

    cout << "-" << endl;
    for (const ChainDesc &c : chains)
    {
        cout << "start_job: " << c.start_job << endl;
        cout << "last_job: " << c.last_job << endl;
        cout << "number_of_jobs: " << c.number_of_jobs << endl;
        cout << "job_chain_runtime: "; format_seconds(c.runtime); cout << endl;
        cout << "average_job_time: "; format_seconds(floor((1. * c.runtime) / c.number_of_jobs)); cout << endl;
        cout << "-" << endl;
    }

    return 0;
}