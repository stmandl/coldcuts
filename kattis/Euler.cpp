/*
https://open.kattis.com/problems/eulerianpath
1. A Graph has an Euler Path if all nodes except two have an even degree
2. copy the Hierholz Algorithm from the CP4 Book1, 


Input
The input consists of several test cases.
Each test case starts with a line with two non-negative integers,  and ,
separated by a single space, where  is the numbers of nodes in the graph and  is the number of edges. Nodes are numbered from  to . Then follow  lines, each line consisting of two (space-separated) integers  and  indicating that there is an edge from  to  in the graph.

Input will be terminated by a line containing 0 0, this line should not be processed.

Output
For each test case, output a line consisting of a space-separated list of the nodes visited by an Eulerian path if one exists (if there are multiple Eulerian paths, any one is acceptable, so for the second case below, 1 0 1 is also a valid solution), or the word Impossible if no Eulerian path exists.
*/


#include <bits/stdc++.h>
using namespace std;


void solve_case(const vector<vector<int>>AL){

}

void do_case() {
    int num_nodes, num_edges;
    cin >> num_nodes;
    cin >> num_edges;
    vector<vector<int>> edges;
    for (int i=0;i<num_nodes;i++) {
        edges.push_back(vector<int>());
    }
    for (int i=0; i<num_edges; i++) {
        int from,to;
        cin >> from;
        cin >> to;
        edges[from].push_back(to);
        //cout << from << "->" << to << endl;
    }
    int num_even_nodes = 0;
    vector<int> odd_nodes;
    for (int i=0; i< edges.size(); i++) {
        const vector<int>& v = edges[i];
        if ((v.size() % 2) == 0) {
            num_even_nodes++;
        } else {
            odd_nodes.push_back(i);
        }
    }
    if (num_even_nodes != num_nodes-2) {
        cout << "Impossible" << endl;
        return;
    }
    cout << "Possible" << endl;
    solve_case(edges);
}

int main() {

    while (!std::cin.eof()) {
        do_case();
    }

    return 0;
}