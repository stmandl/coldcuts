#include <bits/stdc++.h>
using namespace std;


int main() {
    int N;
    scanf("%d", &N);
    vector<int> numbers;
    for (int i=0; i<N; i++) {
	int c;
	scanf("%d", &c);
	numbers.push_back(c);
    }
    for (vector<int>::const_reverse_iterator it = numbers.rbegin(); it != numbers.rend(); it++)
    {
	cout << *it << endl;
    }
    return 0;
}
	
