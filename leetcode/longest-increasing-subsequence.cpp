/*

You are given an integer array coins representing coins of different denominations and an integer
amount representing a total amount of money.

Return the fewest number of coins that you need to make up that amount.
If that amount of money cannot be made up by any combination of the coins, return -1.

You may assume that you have an infinite number of each kind of coin.
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

    int lengthOfLIS(vector<int>& nums) {
        vector<pair<int,int>> subseqs; // len + largest element
        int largest_len = 0;
        unordered_map<int,int> smallest_for_len;
        for (auto n : nums) {
            // check if there is a subseq with smaller element
            bool found_continue = false;
            int sss = subseqs.size();
            for (int p=0; p<sss; p++) {                
                if (subseqs[p].second < n) {                    
                    found_continue=true;
                    int new_len = subseqs[p].first+1;
                    if (smallest_for_len.find(new_len) == smallest_for_len.end() 
                        || smallest_for_len[new_len] > n) {
                        subseqs.push_back(make_pair(new_len,n));
                        largest_len = max(new_len, largest_len);
                        smallest_for_len[new_len] = n;// min(smallest_for_len[new_len], n);
                    }
                }
            }        
            if (!found_continue) {
                subseqs.push_back(make_pair(1,n));
                largest_len = max(largest_len,1);
            }            
        }
        return largest_len;
    }
};

int main()
{       
    // vector<int> coins1{1,2,5};
    // std::cout << Solution().coinChange(coins1, 1) << endl;

    vector<int> ex1{10,9,2,5,3,7,101,18};
    std::cout << Solution().lengthOfLIS(ex1) << endl;

    vector<int> ex2{0,1,0,3,2,3};
    std::cout << Solution().lengthOfLIS(ex2) << endl;

    vector<int> ex3{7,7,7,7,7,7,7};
    std::cout << Solution().lengthOfLIS(ex3) << endl;
    return 0;
}