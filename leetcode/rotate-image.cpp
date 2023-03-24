#include<bits/stdc++.h>
using namespace std;

/*
You are given an n x n 2D matrix representing an image, rotate the image by 90 degrees (clockwise).

You have to rotate the image in-place, which means you have to modify the input 2D matrix directly. DO NOT allocate another 2D matrix and do the rotation.

*/

class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        
        int n = matrix.size()+1;
        // we can rotate in place by "cycling" 4 elements at a time.
        // for x,y < n/2:
        // (x,y) -> (n-y,x)
        // for x>n/2:
        // (x,y) -> (n-y, n-x)
        for (int x=0; x<n/2-1; x++) {
            for (int y=0; y<n/2-1; y++) {
                int tmp = matrix[x][y];
                matrix[x][y] = matrix[y][n-x];
                matrix[y][n-x] = matrix[n-x][n-y];
                matrix[n-x][n-y] = matrix[n-y][x];
                matrix[x][y] = tmp;
                // int w1 = matrix[i][j];
                // int w2 = matrix[i][width-j];
                // int w3 = matrix[height-i][width-j];
                // int w4 = matrix[height-i][j];
            }
        }

    }
};

template<typename T>
ostream& operator<<(ostream& os, vector<T> v) {
    os << "[";
    if (v.size()>0) {
        os << v[0];
        for (size_t i=1; i<v.size(); i++) {
            os << " " << v[i];
        }
    }
    os << "]";
    return os;
}

template<typename T>
ostream& operator<<(ostream& os, vector<vector<T>> v) {
    os << "[";
    if (v.size()>0) {
        os << v[0] << endl;
        for (size_t i=1; i<v.size(); i++) {
            os << " " << v[i];
            if (i<v.size()-1) {
                 os << endl;
            }
        }        
    }
    os << "]";
    return os;
}


int main()
{
    vector<vector<int>> inp1{{1,2,3},{4,5,6},{7,8,9}};
    cout << inp1;
    Solution().rotate(inp1);
    cout << inp1;
    vector<vector<int>> outp1{{7,4,1},{8,5,2},{9,6,3}};
    
    vector<vector<int>> inp2{{5,1,9,11},{2,4,8,10},{13,3,6,7},{15,14,12,16}};
    vector<vector<int>> outp2{{15,13,2,5},{14,3,4,1},{12,6,8,9},{16,7,10,11}};

    return 0;
}