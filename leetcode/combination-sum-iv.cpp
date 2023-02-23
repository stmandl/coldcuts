/*

Given an array of distinct integers nums and a target integer target, return the number of possible combinations that add up to target.

The test cases are generated so that the answer can fit in a 32-bit integer.



 */

#include<bits/stdc++.h>
using namespace std;

template<typename T>
ostream& operator<<(ostream& os, vector<T> v) {
    os << "[";
    if (v.size()>0) {
        cout << v[0];
        for (size_t i=1; i<v.size(); i++) {
            cout << " " << v[i];
        }
    }
    os << "]";
    return os;
}


class Solution {
public:
    int combinationSum4(vector<int>& nums, int target) {        
        vector<long> combs(target+1, 0);
        for (long n:nums) {
            if (n<=target) {
                combs[n] = 1;
            }
        }
        for (int t=1; t<=target; t++) {
            int ts = 0;
            for (int n : nums) {
                if (t-n > 0) {
                    ts += combs[t-n];
                }
            }
            combs[t] += ts;
        }
        return combs[target];
    }
};


int main()
{   
    vector<int> ex1{1,2,3};
    std::cout << Solution().combinationSum4(ex1, 4) << endl;
    vector<int> ex2{9};
    std::cout << Solution().combinationSum4(ex2, 3) << endl;

    return 0;
}