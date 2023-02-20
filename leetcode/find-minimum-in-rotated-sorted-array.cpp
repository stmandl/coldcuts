/*

Idea: 
1. find p such that a[p] > a[p+1]
2. return a[p+1]

def.given a range (i,j), if a[i]<a[j]: no rotation otherwise rotated

choose m with i<=m<=j
if (i,m) is rotated check there, otherwise check (m+1,j) 

 */

#include<bits/stdc++.h>
using namespace std;

class Solution {
public:

    int find_n(vector<int>& nums, int from, int to) {
        if (nums[from] < nums[to]) return 0;
        //cout << "FROM: " << from << " TO: " << to << endl;
        if ( (to%nums.size()) == ((from+1)%nums.size()) ) {
            return to;
        }
        int m = ((from + to)/2)%nums.size();
        //cout << "m=" << m << endl;
        if (nums[(m+1)%nums.size()] < nums[m]) {
            return (m+1)%nums.size();
        }
        if (nums[from] > nums[m]) {
            return find_n(nums, from, m);
        } else {
            return find_n(nums, (m+1)%nums.size(), to);
        }
    }

    int findMin(vector<int>& nums) {
        int n = find_n(nums, 0, nums.size()-1);
        //cout << "rot=" << n << endl;
        return nums[n % nums.size()];
    }
};

int main()
{
    vector<int> ex0{5,1,2,3,4};
    cout << Solution().findMin(ex0) << endl;    
    vector<int> ex1{3,4,5,1,2};
    cout << Solution().findMin(ex1) << endl;
    vector<int> ex2{4,5,6,7,0,1,2};
    cout << Solution().findMin(ex2) << endl;
    vector<int> ex3{11,13,15,17};
    cout << Solution().findMin(ex3) << endl;
    vector<int> ex4{2,1};
    cout << Solution().findMin(ex4) << endl;
    return 0;
}