/*
This problem was asked by Snapchat.

Given a string of digits, generate all possible valid IP address combinations.

IP addresses must follow the format A.B.C.D, where A, B, C, and D are numbers between 0 and 255. Zero-prefixed numbers, such as 01 and 065, are not allowed, except for 0 itself.

For example, given "2542540123", you should return ['254.25.40.123', '254.254.0.123'].
*/

#include <bits/stdc++.h>
using namespace std;

template<typename t>
ostream& operator<<(ostream& os, vector<t> v) {
	os << "[";
	for (int i=0; i<v.size(); i++) {
		os << v[i];
		if (i<v.size()-1)
			os << ",";		
	}
	os << "]";
	return os;
}

string join(vector<string>& parts) {
	return parts[0]+"."+parts[1]+"."+parts[2]+"."+parts[3];
}

void dfs(const string& numbers, int pos, vector<string> parts, vector<string>& results)
{
	if (pos == numbers.size() && parts.size() == 4) {
		results.push_back(join(parts));
		return;
	}
	if (parts.size()==4) {
		return;
	}
	if (pos<numbers.size()) {
		if (numbers[pos] == '0') {
			parts.push_back("0");
			dfs(numbers, pos+1, parts, results);
			parts.pop_back();
		} else {
			for (int i=0;i<3;i++) {
				if (pos+i < numbers.size()) {
					string p = numbers.substr(pos,i+1);
					int pi = stoi(p);
					if (pi >=0 && pi <= 255) {
						parts.push_back(p);
						dfs(numbers,pos+i+1, parts, results);
						parts.pop_back();
					}
				}
			}
		}
	}	      	
}


vector<string> ip_addresses(const string& numbers) {
	vector<string> res;
	dfs(numbers,0,{},res);
	return res;
}

int main() {
	cout << ip_addresses("2542540123");
	return 0;
}
