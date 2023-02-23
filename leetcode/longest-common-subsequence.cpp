/*
Given two strings text1 and text2, return the length of their longest common subsequence. If there is no common subsequence, return 0.

A subsequence of a string is a new string generated from the original string with some characters (can be none) deleted without changing the relative order of the remaining characters.

For example, "ace" is a subsequence of "abcde".
A common subsequence of two strings is a subsequence that is common to both strings.
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
    First off, it seems to be a DP problem as:
    (1) it's listed in this category on https://leetcode.com/discuss/general-discussion/460599/blind-75-leetcode-questions
    (2) it has the optimal subproblem property:
        * the longest common subsequence of texts that are shorter by one character will
          be part of the longest common subsequence of the full text
        * in other words: the choice of a certain character previously does not
          affect the current choice of a character. (only the size matters)
*/

class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        // iterate over the smaller one
        // if (text1.size() > text2.size()) {
        //     swap(text1,text2);
        // }
        vector<vector<int>> cache;
        for (int i=0; i<text1.size()+1; i++) {
            cache.emplace_back(vector<int>(text2.size()+1));
            for (int j=0; j<text2.size()+1; j++) {
                cache.back()[j] = -1;
            }
        }
        return longestCommonSubsequence_rec(text1, 0, text2, 0, cache);
    }
    // -> (len, last_text2_pos)
    int longestCommonSubsequence_rec(string& text1, int p1, string& text2, int p2, vector<vector<int>>& cache) {
        if (cache[p1][p2] < 0) {     
            if (p1 == text1.size() || p2 == text2.size()) {
                cache[p1][p2] = 0;    
            }
            else if (text1[p1] == text2[p2]) {
                cache[p1][p2] = 1+longestCommonSubsequence_rec(text1,p1+1, text2, p2+1, cache);
            } else {
                cache[p1][p2] = max(longestCommonSubsequence_rec(text1, p1+1, text2, p2, cache),
                                    longestCommonSubsequence_rec(text1, p1, text2, p2+1, cache));            
            }
        }   
        return cache[p1][p2]; 
    }
};

int main()
{           
    std::cout << Solution().longestCommonSubsequence("abcde", "ace") << endl;
    std::cout << Solution().longestCommonSubsequence("abc", "abc") << endl;
    std::cout << Solution().longestCommonSubsequence("abc", "def") << endl;
    std::cout << Solution().longestCommonSubsequence("oxcpqrsvwf", "shmtulqrypy") << endl;
    return 0;
} 