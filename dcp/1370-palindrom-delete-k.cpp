/*
This is your coding interview problem for today.

This problem was asked by Google.

Given a string which we can delete at most k, return whether you can make a palindrome.

For example, given 'waterrfetawx' and a k of 2, you could delete f and x to get 'waterretaw'.

We will be sending the solution tomorrow, along with tomorrow's question. As always, feel free to shoot us an email if there's anything we can help with.

Have a great day!
 */

#include <bits/stdc++.h>
using namespace std;


bool check_pali_(const string& s, int left, int right, int k) {
	if (left >= right) return true;
	if (s[left] == s[right]) {
		return check_pali_(s,left+1, right-1, k);
	} else if (k>0) {
		return check_pali_(s, left+1, right, k-1 )
			|| check_pali_(s, left, right-1, k-1);
	}
	return false;
}

bool check_pali(const string& s, int k) {
	return check_pali_(s, 0, s.size()-1, k);
}


int main()
{
	cout << check_pali("waterrfetawx", 2) << endl;
	return 0;
}
