/*
Given a string s and a dictionary of strings wordDict, return true if s can be segmented into a space-separated sequence of one or more dictionary words.

Note that the same word in the dictionary may be reused multiple times in the segmentation.
 */

#include<bits/stdc++.h>
using namespace std;

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
ostream& operator<<(ostream& os, unordered_set<T> v) {
    os << "{";
    for (auto e: v) {
        os << e << " ";
    }
    os << "}";
    return os;
}

class Solution {
public:
    bool wordBreak_rec(string s, vector<string>& wordDict, unordered_map<string,bool>& cache) {
        auto it = cache.find(s);
        if (it != cache.end()) {
            return it->second;
        }
        if (s.size()==0) return true;
        bool foundOne=false;
        for (const auto& w: wordDict) {
            if (s.rfind(w,0) == 0) {
                string subprob = s.substr(w.size(), s.size()-w.size());
                if (wordBreak_rec(subprob, wordDict, cache)) {
                    foundOne = true;
                    cache[subprob] = true;
                    break;              
                }
            }
            if (foundOne) break;
        }
        return foundOne;
    }
    bool wordBreak(string s, vector<string>& wordDict) {
        unordered_map<string,bool> cache;        
        unordered_set<char> wordChars{s.begin(), s.end()};
        unordered_set<char> dictChars;
        for (const auto& w:wordDict) {
            dictChars.insert(w.begin(), w.end());
        }

        for (char c : wordChars) {
            if (dictChars.find(c) == dictChars.end()) return false;
        }

        return wordBreak_rec(s, wordDict, cache);
    }
};

int main()
{   
    Solution s;
    vector<string>wd1{"leet","code"};
    std::cout << s.wordBreak("leetcode", wd1) << endl;
    vector<string>wd2{"apple","pen"};
    std::cout << s.wordBreak("applepenapple", wd2) << endl;
    vector<string>wd3{"cats","dog","sand","and","cat"};
    std::cout << s.wordBreak("catsandog", wd3) << endl;
    vector<string>wd4{"a","aa","aaa","aaaa","aaaaa","aaaaaa","aaaaaaa","aaaaaaaa","aaaaaaaaa","aaaaaaaaaa"};
    std::cout << s.wordBreak("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaab", wd4) << endl;
    vector<string>wd5{"a","b","bbb","bbbb"};
    std::cout << s.wordBreak("bb", wd5) << endl;
    vector<string>wd6{"dog","s","gs"};
    std::cout << s.wordBreak("dogs", wd6) << endl;
    vector<string>wd7{"aa","aaa","aaaa","aaaaa","aaaaaa","aaaaaaa","aaaaaaaa","aaaaaaaaa","aaaaaaaaaa","ba"};
    std::cout << s.wordBreak("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabaabaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", wd7) << endl;
    return 0;
} 