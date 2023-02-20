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



class Solution {
public:
    int getSum(int a, int b) {
        int c;
        int p=0;
        int res=0;

        while (p<=8) {
            bool a1 = a & (1 << p);
            bool b1 = b & (1 << p);
            bool c1 = c & (1 << p);
            cout << "a1=" << a1 << " b1=" << b1 << " c1=" << c1 << endl;
            if (!c1) {
                if ((a1 || b1) && !(a1 && b1)) {
                    res |= 1<<p;
                } else if (a1 && b1) {
                    c=1;
                }
            } else {
                if (a1 && b1) {
                    res |= 1<<p;
                    c=1;
                } else if (a1 || b1) {
                    c=1;
                } else {
                    res |= 1<<p;
                    c=0;
                }
            }
            //a /= 2;
            //b /= 2;
            p++;            
        }
        return res;
    }
};


int main()
{       
    std::cout << Solution().getSum(1,2) << endl;
    std::cout << Solution().getSum(2,3) << endl;

   return 0;
}