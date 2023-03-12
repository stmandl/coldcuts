#include <bits/stdc++.h>
using namespace std;


void merge(vector<int>& v, int from, int half, int to)
{
    assert(from<=to);
    vector<int> buffer;
    buffer.assign(static_cast<size_t>(to-from+1),-0);
    int a = from;
    int b = half;
    int bp = 0;
    while (a<half && b<=to)
    {
        if (v[a]<=v[b]) {
            buffer[bp++] = v[a++];
        } else  {
            buffer[bp++] = v[b++];
        }
    }
    while (a<half) {
        buffer[bp++] = v[a++];
    }
    while (b<=to) {
        buffer[bp++] = v[b++];
    }
    bp=0;
    for (int i = from; i<=to; i++) {
        v[i] = buffer[bp++];
    }
}

void mergesort_(vector<int>& v, int from, int to)
{    
    if (from >= to) return;
    int half = (from + to) / 2;
    mergesort_(v, from, half);
    mergesort_(v, half+1, to);
    merge(v, from, half+1, to);
}

void mergesort(vector<int>& v)
{
    mergesort_(v, 0, v.size()-1);
}


int main()
{
    vector<int> nums = {1,2,5,6,7,9,1,2,3,4,2,23,5,1,2,5,7,-67,-2,-56};
    mergesort(nums);
    for (auto n:nums) {
        cout << n << " ";
    }
    cout << endl;
    return 0;
}