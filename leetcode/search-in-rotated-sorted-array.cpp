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

    int between(int v, int a, int b) {
        if (a <= b) {
            
            return a<=v && v<=b;
        }
        return b<=v && v <= a;
    }


    int search(vector<int>& nums, int target) {
        int l = 0;
        int r = nums.size()-1;

        while (l<=r) {
            int m = (l+r)/2;
            if (nums[m] == target) {
                return m;
            }

            // left sorted
            if (nums[l] <= nums[m]) {
                if (target > nums[m] || target < nums[l]) {
                    l = m+1;
                } else {
                    r = m-1;
                }
            } else {
                if (target > nums[r] || target < nums[m]) {
                    r = m-1;
                } else {
                    l = m + 1;
                }
            }
        }
        return -1;
    }
};


/*

5,1,2,3,4

t=1

*/

int main()
{   
    vector<int> ex6{3,4,5,6,7,1,2};
    cout << Solution().search(ex6, 4) << endl;
    // vector<int> ex5{5,1,2,3,4};
    // cout << Solution().search(ex5, 1) << endl;
    // vector<int> ex0{5,1,3};
    // cout << Solution().search(ex0, 3) << endl;
    // vector<int> ex1{4,5,6,7,0,1,2};
    // cout << Solution().search(ex1, 0) << endl;    
    // vector<int> ex2{4,5,6,7,0,1,2};
    // cout << Solution().search(ex2, 3) << endl;
    // vector<int> ex3{1};
    // cout << Solution().search(ex3, 0) << endl;
    return 0;
}