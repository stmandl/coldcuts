#include <bits/stdc++.h>
#include <cstddef>
#include <cstring>
using namespace std;

using Fact = tuple<string, double, string>;
using Query = tuple<double,string,string>;
using Graph = unordered_map<string,vector<pair<string,double>>>;

Graph compile_facts(const vector<Fact>& facts) {
    Graph result;
    for (const auto& f : facts) {
        result[get<0>(f)].push_back(make_pair(get<2>(f),get<1>(f)));
        result[get<2>(f)].push_back(make_pair(get<0>(f),1./get<1>(f)));
    }
    return result;
}

double query_(Query q, Graph G, bool& succ, unordered_set<string> history) {
    double amount = get<0>(q);
    string from = get<1>(q);
    string to = get<2>(q);
    if (from == to) {
        succ = true;
        return amount;
    }
    if (history.find(from) != history.end()) {
        succ = false;
        return -1;
    }
    history.insert(from);
    for (const auto& n : G[from]) {
        double res = query_(make_tuple(amount*n.second,n.first,to), G, succ, history);
        if (succ) {
            return res;
        }
    }
    succ = false;
    return -1;
}    

double query(Query q, Graph G, bool& succ) {
    unordered_set<string> history;
    return query_(q, G, succ, history);
}

int main()
{
    vector<Fact> facts{{"m",3.28,"ft"},
                       {"ft",12,"in"},
                       {"hr",60,"min"},
                       {"min",60,"sec"}};

    vector<Query> queries{{2,"m","in"},
                          {13,"in","m"},
                          {13,"in","hr"}};

    Graph G = compile_facts(facts);
    
    for (const auto& q : queries) {
        bool success=true;
        double res = query(q, G, success);
        if (!success) {
            cout << get<0>(q) << get<1>(q) << " conversion to " << get<2>(q) << " not supported" << endl;
        } else {
            cout << get<0>(q) << get<1>(q) << " = " << res << get<2>(q) << endl;
        }
    }

    return 0;
}

