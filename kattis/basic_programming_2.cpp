#include <bits/stdc++.h>
using namespace std;

void task1(vector<int>& inp)
{
    for (int i=0; i<inp.size()-1; i++) {
	int a = inp[i];
	if (a<=7777) {
	    for (int j=i+1; j<inp.size(); j++) {
		if (inp[j]+a == 7777) {
		    cout << "Yes";
		    return;
		}
	    }
	}
    }
    cout << "No";
}
void task2(vector<int>& inp)
{
    unordered_set<int> m(inp.begin(), inp.end());
    if (m.size() == inp.size()) {
	cout << "Unique";
    } else {
	cout << "Contains duplicate";
    }
}
void task3(vector<int>& inp)
{
    unordered_map<int, size_t> counts;
    for (int i : inp) {
	counts[i] += 1;
    }
    int N = inp.size()/2;
    for (auto it : counts) {
	if (it.second > N) {
	    cout << it.first;
	    return;
	}
    }
    cout << -1;
}
void task4(vector<int>& inp)
{
    sort(inp.begin(), inp.end());
    if ((inp.size() % 2) == 0) {
	// 0 1 2 | 3 4 |  5 6 7 :: 8/2-1 8/2
	cout << inp[inp.size()/2-1] << " " << inp[inp.size()/2];
    } else {
       // 0 1 2 | 3 | 4 5 6 :: 7/2
	cout << inp[inp.size()/2];
    }
}
void task5(vector<int>& inp)
{
    unordered_map<int, size_t> counts;
    for (int i : inp) {
	counts[i] += 1;
    }
    bool very_first = true;
    for (int i = 100; i<=999; i++) {
	auto it = counts.find(i);
	if (it != counts.end()) {
	    for (int j=0; j<it->second; j++) {
		if (!very_first) {
		    cout << " ";
		}
		cout << it->first;
		very_first = false;
	    }
	}
    }
}

template<typename T>
ostream& operator<<(ostream& out, const vector<T>& vec)
{
    size_t vector_size = vec.size();
    if (vector_size != 0) {
	for (size_t i=0; i<vector_size; i++)
	{
	    out << vec[i];
	    if (i<vector_size-1)
	    {
		cout << ",";
	    }
	}
    }
    return out;
}

int main() {
    int N, t;
    cin >> N; cin >> t;
    vector<int> inp;   
    for (int i=0; i<N; i++) {
	int n;
	cin >> n;
	if (t==1 && n>7777)
	    continue;
	inp.push_back(n);
    }
    //cout << "N: " << N << " t: " << t << endl;
    //cout << inp << endl;
    switch(t) {
    case 1:
	task1(inp);
	break;
    case 2:
	task2(inp);
	break;
    case 3:
	task3(inp);
	break;
    case 4:
	task4(inp);
	break;
    case 5:
	task5(inp);
	break;
    default:
	abort();
    }
    return 0;
}
