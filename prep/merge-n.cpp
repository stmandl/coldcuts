#include <bits/stdc++.h>
using namespace std;

template <typename T>
ostream &operator<<(ostream &os, const vector<T> &v) noexcept {
  if (v.size() == 0)
    return os;
  os << v[0];
  for (decltype(v.cbegin()) it = v.cbegin() + 1; it != v.cend(); ++it) {
    os << " " << *it;
  }
  return os;
}


bool positions_done(const vector<size_t>& pos, const vector<size_t>& sizes) {
    assert(pos.size() == sizes.size());
    for (size_t p = 0; p<pos.size(); p++) {
        if (pos[p] < sizes[p]) {
            return false;
        }
    }
    return true;
}

template<typename T>
size_t next_best_position(const vector<vector<T>>& vs, const vector<size_t>& pos, const vector<size_t> sizes) {
    assert(pos.size() == sizes.size());
    assert(vs.size() == sizes.size());

    size_t n=0;
    T min = numeric_limits<T>::max();
    //cerr << "MIN=" << min;
    for (size_t p = 0; p<pos.size(); p++) {
        if (pos[p] < sizes[p]) {
            // p is still not exausted
            if (vs[p][pos[p]] <= min) {
                n = p;
                min = vs[p][pos[p]];
            }
        }
    }
    return n;
}


template<typename T>
vector<T> merge(vector<vector<T>>& vs) {
    vector<size_t> sizes;

    for (auto& v : vs) {
        sort(v.begin(), v.end());
        sizes.push_back(v.size());
    }
    // to merge, we need one position pointer per vector
    vector<size_t> pos;
    pos.assign(vs.size(), 0);

    vector<T> result;

    while (!positions_done(pos, sizes)) {    
        size_t n = next_best_position(vs, pos, sizes);        
        result.push_back(vs[n][pos[n]]);
        pos[n] += 1;        
    }
    return result;
}

int main() {
    vector<vector<int>> vs;
    vs.emplace_back(10);
    iota(vs[0].begin(), vs[0].end(), 0);
    vs.emplace_back(10);
    iota(vs[1].begin(), vs[1].end(), 0);
    vs.emplace_back(10);
    iota(vs[2].begin(), vs[2].end(), 0);

    for (const auto& v : vs) {
        cout << v << endl;
    }


    vector<int> m = merge(vs);

    cout << m << endl;

    return 0;
}