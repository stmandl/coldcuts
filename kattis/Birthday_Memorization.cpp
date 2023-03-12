#include <bits/stdc++.h>
using namespace std;


int main() {
    int N;
    scanf("%d", &N);
    unordered_map<string, pair<int, string>> pos;
    for (int i=0; i<N; i++) {
	string name;
	int weight;
	string date;
	cin >> name;
	cin >> weight;
	cin >> date;

	auto it = pos.find(date);
	if (it == pos.end() || it->second.first < weight) {
	    pos[date] = make_pair(weight, name);
	}
    }
    vector<string> out;
    for (auto p : pos) {
	out.push_back(p.second.second);
    }
    sort(out.begin(), out.end());
    cout << out.size() << endl;
    for (auto& s : out) {
	cout << s << endl;
    }
    return 0;
}
	
