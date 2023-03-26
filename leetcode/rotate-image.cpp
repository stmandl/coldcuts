#include<bits/stdc++.h>
using namespace std;

/*
You are given an n x n 2D matrix representing an image, rotate the image by 90 degrees (clockwise).

You have to rotate the image in-place, which means you have to modify the input 2D matrix directly. DO NOT allocate another 2D matrix and do the rotation.

*/

template<typename T1, typename T2>
ostream& operator<<(ostream& os, pair<T1,T2> v) {
    os << "(" << v.first << "," << v.second << ")";
    return os;
}

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


void rotate_round(vector<vector<int>>&matrix, int offset, int x, int y) {
    int n = matrix.size();
    vector<pair<int,int>> swap_positions{
        {offset+x,offset+y},
        {n-y-1-offset,x+offset},
        {n-x-1-offset,n-y-1-offset},
        {y+offset,n-x-1-offset}};
    const pair<int,int>& pos_ = swap_positions.back();  
    int tmp0 = matrix[pos_.second][pos_.first];
    const pair<int,int>& pos0 = swap_positions.front();  
    int tmp = matrix[pos0.second][pos0.first];
    // cerr << "temp0:" << tmp0 << endl;
    for (int p = 1; p<swap_positions.size(); p++) {            
        const pair<int,int>& pos1 = swap_positions[p];
        int ntmp = matrix[pos1.second][pos1.first];
        // cerr << " @" << pos1 << ":tmp:" << tmp << " ntmp: " << ntmp << endl;
        matrix[pos1.second][pos1.first] = tmp;
        tmp = ntmp;
    }
    matrix[pos0.second][pos0.first] = tmp;
    // const pair<int,int>& pos = swap_positions[0];
    // matrix[pos.second][pos.first] = tmp;
    
    cerr << swap_positions << endl;
}

void rotate_band(vector<vector<int>>& matrix, int offset) 
{
    int n=matrix.size()-offset;
    cerr << "rotate_band, n=" << n << " n/2=" << n/2 << endl;
    for (int x=0; x<n; x++) {
        rotate_round(matrix, offset, x, 0);
    }
}

class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        
        int n = matrix.size();
        // we can rotate in place by "cycling" 4 elements at a time.
        // for x,y < n/2:
        // (x,y) -> (n-y,x)
        // for x>n/2:
        // (x,y) -> (n-y, n-x)
        // for (int offset = 0; offset <= n/2; offset++) {
        //     rotate_band(matrix, offset);
        // }
        

        for (int x=0; x<n/2; x++) {
            for (int y = x; y<n-x-1; y++) {
                int tmp = matrix[y][x];
                matrix[y][x] = matrix[n-1-x][y];
                matrix[n-1-x][y] = matrix[n-1-y][n-1-x];
                matrix[n-1-y][n-1-x] = matrix[x][n-1-y];
                matrix[x][n-1-y] = tmp;
            }
        }

    }
};



int main()
{
    vector<vector<int>> inp1{{1,2,3},{4,5,6},{7,8,9}};
    cerr << inp1 << endl;
    Solution().rotate(inp1);
    cerr << inp1 << endl;
    vector<vector<int>> outp1{{7,4,1},{8,5,2},{9,6,3}};
    cerr << outp1 << endl;
    
    vector<vector<int>> inp2{{5,1,9,11},{2,4,8,10},{13,3,6,7},{15,14,12,16}};
    cerr << inp2 << endl;
    Solution().rotate(inp2);
    cerr << inp2 << endl;
    vector<vector<int>> outp2{{15,13,2,5},{14,3,4,1},{12,6,8,9},{16,7,10,11}};
    cerr << outp2 << endl;

    return 0;
}