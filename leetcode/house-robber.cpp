/*

You are a professional robber planning to rob houses along a street.
Each house has a certain amount of money stashed, the only constraint stopping
you from robbing each of them is that adjacent houses have security systems
connected and it will automatically contact the police if two adjacent houses
were broken into on the same night.

Given an integer array nums representing the amount of money of each house, 
return the maximum amount of money you can rob tonight without alerting the police.


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


// class Solution {
// public:
//     int rob(vector<int>& nums) {
//         if (nums.size()==1) {
//             return nums[0];
//         }
//         if (nums.size()==2) {
//             return max(nums[0], nums[1]);
//         }
//         vector<int> sol(nums.size(), 0);
//         sol[0] = nums[0];
//         sol[1] = max(nums[0], nums[1]);
//         for (int i=2; i<nums.size(); i++) {
//             sol[i] = max(sol[i-1], nums[i]+sol[i-2]);
//         }
//         return sol.back();
//     }
// };

class Solution {
public:
    int rob(vector<int>& nums) {

        int a = 0;
        int b = nums[0];
        int c = b;
        for (int i=1; i<nums.size(); i++) {
            int use_i = nums[i] + a;
            c = max(use_i, b);
            a = b;
            b = c;
        }
        return c;
    }
};

int main()
{   
    vector<int> ex1{1,2,3,1};
    std::cout << Solution().rob(ex1) << endl;
    vector<int> ex2{2,7,9,3,1};
    std::cout << Solution().rob(ex2) << endl;

    return 0;
}