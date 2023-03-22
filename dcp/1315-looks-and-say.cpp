/*
This is your coding interview problem for today.

This problem was asked by Epic.

The "look and say" sequence is defined as follows: beginning with the term 1,
each subsequent term visually describes the digits appearing in the previous term. The first few terms are as follows:

1
11
21
1211
111221

As an example, the fourth term is 1211, since the third term consists of one 2 and one 1.

Given an integer N, print the Nth term of this sequence.
*/

#include <bits/stdc++.h>
using namespace std;

// naive implementation
string rle(string s) {
    string res;
    int p = 0;    
    while (p<s.size()) {        
        int count = 1;
        char current = s[p];
        while (p < s.size() && s[p+1] == current) {
            count++;
            p++;
        }
        p++;
        res += to_string(count) + to_string(current-'0');
    }
    return res;
}

int main() {
    string s = "1";
    for (int i=2; i<10; i++) {
        cout << s << endl;
        s = rle(s);
    }
    return 0;
}

