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

/*

 */


// class Solution {
// public:
//     int cC(vector<int>& coins, int amount) {
//         //cout << "cC("<<amount<<")" << endl;
//         if (amount < 0) {
//             return -1;
//         }
//         if (amount == 0) {
//             return 0;
//         }
//         for (auto c : coins) {
//             //cout << "A=" << amount << " c=" << c << endl;
//             int sub = cC(coins, amount - c);
//             if (sub != -1) {
//                 return 1+sub;
//             }
//         }
//         return -1;
//     }
//     int coinChange(vector<int>& coins, int amount) {
//         sort(coins.begin(),coins.end(), [](int a, int b)->bool{return a>b;});
//         return cC(coins, amount);
//     }
// };



class Solution {
public:

    int coinChange(vector<int>& coins, int amount) {
        sort(coins.begin(),coins.end(), [](int a, int b)->bool{return a>b;});
        vector<int> tab;
        tab.assign(amount+1,-1);
        tab[0] = 0;
        for (int a = 1; a<=amount; a++) {
            int min_ways = numeric_limits<int>::max();
            for (auto c: coins) {                
                if ((a-c) >= 0 && tab[a-c]>=0) {
                    min_ways = min(min_ways, tab[a-c]+1);                    
                }
            }
            if (min_ways != numeric_limits<int>::max()) {
                tab[a] = min_ways;
            }
        }
        //cout << "TTT:" << tab << endl;
        return tab[amount];
    }
};

int main()
{       
    // vector<int> coins1{1,2,5};
    // std::cout << Solution().coinChange(coins1, 1) << endl;

    vector<int> coins1{1,2,5};
    std::cout << Solution().coinChange(coins1, 11) << endl;

    vector<int> coins2{2};
    std::cout << Solution().coinChange(coins2, 3) << endl;

    vector<int> coins3{1};
    std::cout << Solution().coinChange(coins2, 0) << endl;
    return 0;
}