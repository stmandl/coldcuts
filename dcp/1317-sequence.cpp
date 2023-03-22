#include <bits/stdc++.h>
using namespace std;


// approach 1: brute force search
bool satisfies(const vector<int>&s1, const vector<char>&p) {
    for (int pos = 1; pos<s1.size(); pos++ ) {
        switch (p[pos]) {
            case '+':
            if (s1[pos] < s1[pos-1]) return false;
            break;
            case '-':
            if (s1[pos] > s1[pos-1]) return false;
            break;
            defaut:
            abort();
        }
    }
    return true;
}

struct State {
    vector<int> seq;
    set<int> remaining;
    State(vector<int>s, set<int>r) : seq(s), remaining(r) {};
    bool operator<(const State&o)  const{
        return seq < o.seq;
    }
};

vector<int> unjumble(const vector<char>& pat)
{

    vector<State> agenda;
    for (int i = 1; i<= pat.size(); i++) {
        set<int> remain;
        for (int j=1; j<=pat.size(); j++) {
            if (i!=j) remain.insert(j);
        }
        vector<int> s {i};
        agenda.emplace_back(s,remain);
    }

    while (agenda.size()>0) {
        State current = agenda.back();
        agenda.pop_back();
        if (satisfies(current.seq, pat)) {
            if (current.remaining.size() == 0) {
                return current.seq;
            }
            // generate possible successors
            for (auto n : current.remaining) {
                set<int> new_newmain;
                for (auto nn : current.remaining) {
                    if (nn != n) {
                        new_newmain.insert(nn);
                    }
                }
                vector<int> news(current.seq.begin(), current.seq.end());
                news.push_back(n);
                if (satisfies(news,pat)) {
                    agenda.emplace_back(news, new_newmain);
                }
            }
        }
    }
    return {};
}


// direct recursion
vector<int> unjumble2_rec(vector<int>seq, set<int> cand, const vector<char>& pat)
{
    cout << "unjumble2_rec: [";
    for (auto c: seq) cout << c << " ";
    cout << "] / {";
    for (auto c: cand) cout << c << " ";
    cout << "}" << endl;
    if (!satisfies(seq,pat)) return {};
    if (cand.size()==0) return seq;
    for (auto c:cand) {
        set<int> new_cand;
        for (auto cc:cand) {
            if (cc != c) new_cand.insert(cc);
        }
        vector<int> new_seq(seq);
        new_seq.push_back(c);
        auto res = unjumble2_rec(new_seq, new_cand, pat);
        if (res.size() > 0) return res;
    }
    return {};
}
vector<int> unjumble2(const vector<char>& pat)
{

    for (int i = 1; i<= pat.size(); i++) {
        set<int> cand;        
        for (int j=1; j<=pat.size(); j++) {
            if (i!=j) cand.insert(j);
        }
        vector<int> seq {i};
        auto res = unjumble2_rec(seq,cand,pat);
        if (res.size() > 0) return res;
    }
    return {};
}

int main() {
    vector<char> seq {
        '/', '+', '+', '-', '-'
    };
    for (auto i : unjumble(seq)) {
        cout << i << endl;
    }
    return 0;
}