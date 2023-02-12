#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <cassert>

using namespace std;

enum class Code {ok=27,                 
                 missing_opening_parenthesis,
                 missing_closing_parenthesis,
                 missing_comma,
                 incomplete_input,
                 duplicate_pair,
                 no_more_child_possible,                 
                 cyclic,
                 multiple_roots};


unordered_map<Code,string> error_texts {{Code::missing_opening_parenthesis,"E1"},
                                        {Code::missing_closing_parenthesis,"E1"},
                                        {Code::missing_comma,"E1"},
                                        {Code::incomplete_input,"E1"},
                                        {Code::duplicate_pair,"E2"},
                                        {Code::no_more_child_possible,"E3"},
                                        {Code::cyclic, "E4"},
                                        {Code::multiple_roots, "E5"}};


constexpr char NIL = -1;

// This compact struct deal with several error cases
// and is also very lightweight.
struct Children
{
    char child1 = NIL;
    char child2 = NIL;
 
    Code Add(char child) {
        
        // duplicate check
        if (child1 == child || child2 == child) {
            return Code::duplicate_pair;
        }
        
        // insert in correct position
        if (child1 == NIL) {
            child1 = child;
        } else if (child2 == NIL) {
            child2 = child;
        } else {
            return Code::no_more_child_possible;
        }

        return Code::ok;
    }
    
    // .. needed to be useable in unordered_map
    bool operator==(const Children other) const {
        return child1 == other.child1 && child2 == other.child2;
    }
    
};

// ... needed to be usable in unordered_map
namespace std {
    template<>
    struct hash<Children> {
        size_t operator()(const Children& c) const {
            return static_cast<size_t>(c.child1)+static_cast<size_t>(c.child2)*256L;
        }
    };
}

class BTree
{
private:
    unordered_map<char, Children> successors;
    unordered_set<char> possible_roots;
    bool roots_are_computed = false;
    bool cycles_are_checked = false;

    /**
     * This member function removes all nodes that appear
     * as successors from the set of possuble roots.
     * At the end, there must be exactly one such node.  
     */
    Code ComputeRoots() {        
        for (const auto& rel : successors) {            
            if (rel.second.child1 != NIL) {
                possible_roots.erase(rel.second.child1);
            }
            if (rel.second.child2 != NIL) {
                possible_roots.erase(rel.second.child2);
            }            
        }
        if (possible_roots.size() > 1) {
            return Code::multiple_roots;
        } else if (possible_roots.size() == 0) {
            return Code::cyclic;
        }
        roots_are_computed = true;
        return Code::ok;        
    }
    
    /** 
     * This member function detects cycles
     * by traversing the tree starting at the root
     * and marking all nodes visited. Once a node
     * is visited twice, a cycle is detected.
     */
    Code CheckCycles() {
        assert(roots_are_computed);
        unordered_set<char> visi3ted;
        vector<char> agenda;
        agenda.push_back(*possible_roots.begin());
        while (agenda.size()>0) {
            char current = agenda.back();
            agenda.pop_back();
            if (visited.find(current) != visited.end()) {
                return Code::cyclic;
            }
            visited.insert(current);
            const auto& succ = successors.find(current);            
            if (succ != successors.end()) {
                if (succ->second.child2 != NIL) {
                    agenda.push_back(succ->second.child2);
                }
                if (succ->second.child1 != NIL) {
                    agenda.push_back(succ->second.child1);
                }
            }
        }
        cycles_are_checked = true;
        return Code::ok;
    }
    
    bool Valid() {
        return roots_are_computed && cycles_are_checked;
    }
    
    void PrintSubtree(char node) {        
        cout << "(" << node;
        const auto& succ = successors.find(node);
        if (succ != successors.end()) {
            char a = succ->second.child1;
            char b = succ->second.child2;
            if (b == NIL) {
                PrintSubtree(a);
            } else {
                if (a <= b) {
                    PrintSubtree(a);
                    PrintSubtree(b);
                } else {            
                    PrintSubtree(b);
                    PrintSubtree(a);
                }
            }
        }
        cout << ")";
    }
    
    
public:
    Code AddRelation(char parent, char child) {
        
        // once validated, we must not change the tree anymore
        // actually depending on the context, abort() or exceptions
        // might be a better alternative to "assert"
        assert(!Valid());

        // only the parent might be the root
        possible_roots.insert(parent);
        
        // update the succesor relation
        auto& succ = successors[parent];                
        return succ.Add(child);
    }
    
    Code Validate() {
        Code ec = ComputeRoots();
        if (ec != Code::ok) {
            return ec;
        }
        return CheckCycles();
    }
    
   
    void Print() {
        assert(Valid());        
        PrintSubtree(*possible_roots.begin());  
    }
};


Code read_pair(const string& input, size_t& pos, vector<pair<char,char>>& pairs) {
    if (input[pos++] != '(') return Code::missing_opening_parenthesis;
    if (pos >= input.size()) return Code::incomplete_input;
    char parent = input[pos++];
    if (pos >= input.size()) return Code::incomplete_input;
    if (input[pos++] != ',') return Code::missing_comma;
    if (pos >= input.size()) return Code::incomplete_input;
    char child = input[pos++];
    if (pos >= input.size()) return Code::incomplete_input;
    if (input[pos++] != ')') return Code::missing_closing_parenthesis;
    pairs.emplace_back(parent, child);
    return Code::ok;
}



int main() {
    
    // I choose a quite strict parser.
    // If I'd have more experience with C++ regexp, I'd probably gave them a try.
    string input;
        
    getline(cin, input);
        
    // read the input
    size_t pos = 0;  
    vector<pair<char,char>> pairs;
    while (pos < input.size())
    {
        if (pos > 0 && input[pos++] != ' ') {
            cout << "E1";
            return 0;
        }
                
        Code ec = read_pair(input, pos, pairs);
        if (ec != Code::ok) {
            cout << error_texts[ec];
            return 0;
        }
    }
    
    // Check for duplicate entries
    set<pair<char,char>> rels(pairs.begin(), pairs.end());
    if (pairs.size() != rels.size()) {
        cout << error_texts[Code::duplicate_pair];
        return 0;
    }
    
    // Construct the tree
    BTree tree;
    for (const auto& rel : rels) {
        Code ec = tree.AddRelation(rel.first, rel.second);
        if (ec != Code::ok) {
            cout << error_texts[ec];
            return 0;            
        }
    }
    
    // Check for more errors
    Code ec = tree.Validate();
    if (ec != Code::ok) {
        cout << error_texts[ec];
        return 0;
    }
    
    // Finally print the S-expression for the tree
    tree.Print();
    
    return 0;
}