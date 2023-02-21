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
//     int climbStairs(int n) {
//         if (n == 0) {
//             return 0;
//         } else if (n == 1) {
//             return 1;
//         } else if (n == 2) {
//             return 2;
//         } else {
//             return climbStairs(n-1) + climbStairs(n-2);
//         }
//     }
// };

class Solution {
public:
    int climbStairs(int n) {        
        if (n == 0) {
            return 0;
        } else if (n == 1) {
            return 1;
        } else if (n == 2) {
            return 2;
        } else {
            int n_m2 = 1;
            int n_m1 = 2;
            int current = -1;
            for (int i = 3; i<=n; i++) {
                current = n_m2 + n_m1;
                int tmp = n_m1;
                n_m1 = current;
                n_m2 = tmp;
            }
            return current;
        }
    }
};

int main()
{       
    std::cout << Solution().climbStairs(2) << endl;
    std::cout << Solution().climbStairs(3) << endl;
    //auto begin = chrono::high_resolution_clock::now();
    std::cout << Solution().climbStairs(45) << endl; //1836311903
    //auto duration = chrono::high_resolution_clock::now() - begin;
    //cout << duration.count() << endl;
    return 0;
}