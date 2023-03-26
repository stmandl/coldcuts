/*
Given an m x n grid of characters board and a string word, return true if word exists in the grid.

The word can be constructed from letters of sequentially adjacent cells, where adjacent cells are horizontally or vertically neighboring. The same letter cell may not be used more than once.

*/

#include <bits/stdc++.h>
using namespace std;

template<typename t>
ostream& operator<<(ostream& os, vector<t> v) {
	os << "[";
	for (int i=0; i<v.size(); i++) {
		os << v[i];
		if (i<v.size()-1)
			os << ",";		
	}
	os << "]";
	return os;
}

struct Pos {
	int x, y;
	Pos(int x_, int y_) : x(x_), y(y_) {};
	Pos left() const {
		return Pos(x-1,y);
	}
	Pos right() const {
		return Pos(x+1,y);
	}
	Pos up() const {
		return Pos(x,y-1);
	}
	Pos down() const {
		return Pos(x,y+1);
	}
	
};


bool operator==(const Pos& a, const Pos& b) {
	return a.x == b.x && a.y == b.y;
}

namespace std {
	template<>
	struct hash<Pos> {
		size_t operator()(const Pos& p) const {
			return p.x+p.y*37;
		}
	};
}


bool valid_pos(const vector<vector<char>>& board, const Pos& pos) {
	int height=board.size();
	int width=board[0].size();
	return pos.x >=0 && pos.x < width && pos.y >=0 && pos.y < height;
}

vector<Pos> followers(const vector<vector<char>>& board, const Pos& pos,  unordered_set<Pos>& visited) {
	vector<Pos> res;
	Pos p=pos.left();
	if (valid_pos(board, p) && visited.find(p) == visited.end()) {
		res.push_back(p);
	}
	p=pos.right();
	if (valid_pos(board, p) && visited.find(p) == visited.end()) {
		res.push_back(p);
	}
	p=pos.up();
	if (valid_pos(board, p) && visited.find(p) == visited.end()) {
		res.push_back(p);
	}
	p=pos.down();
	if (valid_pos(board, p) && visited.find(p) == visited.end()) {
		res.push_back(p);
	}
	return res;
}

bool search_(const vector<vector<char>>& board, const string& word, int strpos, Pos array_pos, unordered_set<Pos>& visited)
{
	if (strpos == word.size()) {
		return true;
	}
	if (board[array_pos.y][array_pos.x] != word[strpos]) {
		return false;
	}
	visited.insert(array_pos);
	for (auto p : followers(board, array_pos, visited)) {
		if (search_(board, word, strpos+1, p, visited)) {
			return true;
		}
	}
	return false;
}

bool search(const vector<vector<char>>& board, const string& word) {
	int height=board.size();
	int width=board[0].size();
	for (int y=0; y<height; y++) {
		for (int x=0; x<width; x++) {
			unordered_set<Pos> visited;
			if (search_(board, word, 0, Pos(x,y), visited)) {
				return true;
			}
		}
	}
	return false;
}

int main() {
	vector<vector<char>> board1{
		{'A','B','C','E'},
		{'S','F','C','S'},
		{'A','D','E','E'}
	};
	cout << search(board1, "ABCCED") << endl;
	vector<vector<char>> board2{
		{'A','B','C','E'},
		{'S','F','C','S'},
		{'A','D','E','E'}
	};
	cout << search(board2, "SEE") << endl;
	vector<vector<char>> board3{
		{'A','B','C','E'},
		{'S','F','C','S'},
		{'A','D','E','E'}
	};
	cout << search(board3, "ABCB") << endl;
	return 0;
}
