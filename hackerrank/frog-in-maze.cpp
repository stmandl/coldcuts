#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

struct Pos {
  int i,j;  
  Pos(int i_, int j_) : i(i_), j(j_) {}
  bool operator==(const Pos& other) const {
      return i == other.i && j == other.j;
  }
  Pos& operator=(const Pos& other) {
      i = other.i;
      j = other.j;
      return *this;
  }
  Pos() {
      i=-1;
      j=-1;
  }
};

Pos noPos(-1,-1);

ostream& operator<<(ostream& os, const Pos& p) {
    os << "(" << p.i << "," << p.j << ")";
    return os;
}

namespace std {
template<>
struct hash<Pos> {
    size_t operator()(const Pos& p) const {
        return p.i*(p.j+10)*(p.j+10);
    }
};
}

// TODO:
// AS FLOW PROBLEM:
// directed flow graph mit probability als capacities
// an einem anderen Tag

class Maze
{
public:
    vector<string> rows;
    unordered_map<Pos /* from */, Pos /* to */> tunnels;
    Pos frogPosition;
    int numColumns;
    int numRows;
    vector<vector<bool>> visited;
    unordered_map<int,vector<int>> follow_positions;
    vector<bool> mines;
    vector<bool> exits;
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen; // seed the generator


    Maze(int num_rows, int num_columns) : frogPosition(noPos), numRows(num_rows),
					  gen(rd())
	{
	}
    void setNumColumns(int nc) {numColumns = nc;}
    void addRow(string&& r) {
        rows.push_back(r);
    }
    void addTunnel(const Pos& from, const Pos& to) {
        tunnels[from] = to;
    }
    void setFrogPosition(const Pos& p) {
        frogPosition = p;
    }
    void createVisitedMap() {
        for (int r=0; r<numRows; r++) {
            visited.emplace_back(vector<bool>(numColumns, true));
        }
    }
    
    char current() {
        return rows[frogPosition.i][frogPosition.j];
    }
    
    char get(int i, int j) {
        return rows[i][j];    
    }
    char get(const Pos& p) {
        return rows[p.i][p.j];    
    }
    int pos_num(int i, int j) {
        return i*numColumns+j;
    }
    int pos_num(const Pos&p) {
        return pos_num(p.i, p.j);
    }
    bool valid(const Pos& p)  {
	return p.i>=0 && p.j>=0 && p.i<numRows && p.j<numColumns;
    }
    vector<Pos> getFollowPositions(Pos&& p) {
        return {{p.i-1, p.j}, {p.i+1, p.j}, {p.i,p.j-1}, {p.i,p.j+1}};
    }
    void createConnectionGraph() {
        mines.assign(numColumns*numRows,false);
        exits.assign(numColumns*numRows,false);
        for (int i=0; i<numRows; i++) {
            for (int j=0; j<numColumns; j++) {
                int node_number = pos_num(i,j);
                char current = get(i,j);
                if (current == '#') {
                    continue;
                }
                if (current == '*') {
                    mines[node_number] = true;
		    continue;
                }
                if (current == '%') {
                    exits[node_number] = true;
		    continue;
                }
                assert (current == 'A' || current == 'O');
                vector<Pos> next_postitions = getFollowPositions({i,j});
                for (const Pos& p : next_postitions) {
		    //cerr << "CCG: at " << Pos{i,j} << " considering follow-position " << p << " ";
                    if (!valid(p))
		    {
			//cerr << " NOT VALID .. SKIPPED" << endl;
			continue;
		    }
                    char c = get(p);
                    if (c == '#') {
			//cerr << " WALL .. SKIPPED" << endl;
			continue;
		    }
                    auto npos = tunnels.find(p);
                    if (npos != tunnels.end()) {
			//cout << "CCG: at " << Pos{i,j} << " via " << p <<  " tunnel to " << npos->second << endl;
                        follow_positions[node_number].push_back( 
                          pos_num(npos->second.i, npos->second.j)
                        );
                    } else {
			//cerr << " VALID : ADDED!" << endl;
                         follow_positions[node_number].push_back( 
                          pos_num(p.i, p.j)
                        );
                    }
                }
            }
        }
    }


    Pos indexToPos(int idx) {
	return {idx / numColumns, idx % numColumns};
    }

    void printConnectionGraph()	{
	for (const auto& it : follow_positions) {
	    cout << indexToPos(it.first) << " -> ";
	    for (auto n : it.second) {
		cout << indexToPos(n) << ",";
	    }
	    cout << endl;
	}
    }
	    
    
    int run() {
	int current = pos_num(frogPosition);
	int steps_left=100;
	while (steps_left--) {
	    if (exits[current]) {
		//cerr << "RE " << steps_left << endl;
		return 1;
	    }
	    if (mines[current]) {
		//cerr << "RM " << steps_left << endl;
		return 0;
	    }
	    const vector<int>& f = follow_positions[current];
	    if (f.size()==0){
		//cerr << "RS " << steps_left << endl;
		return 0;
	    }
	    //int r = distr(gen);
	    //cerr << "r=" << r << " % " << f.size() << endl;
	    //int n = rand() % f.size();
	    std::uniform_int_distribution<> distr(0, f.size()-1);
	    int n = distr(gen);
	    //cerr << n << endl;
	    current = f[n];
	}
	return -1;
    }
    
    // here is the actual algorithm
    double computeProbability() {
	double num_succ = 0;
	double num_attempts = 0;
	for (int i=0; i<10000; i++) {
	    int r = run();
	    //cerr << "R=" << r << endl;
	    if (r < 0) {
		continue;
	    } else {	
		num_succ += r;
		num_attempts += 1;
	    }
	}
	return num_succ / num_attempts;
    }
};

int main()
{

    // int a0=0,a1=0;
    // for (int i=0; i<100000; i++) {
	// if (rand()%4 == 0) a0++;
	// a1++;
    // }
    // cerr << (1.0*a0)/(1.0*a1) << endl;
    // return 0;
    
    string first_multiple_input_temp;
    getline(cin, first_multiple_input_temp);

    vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

    int n = stoi(first_multiple_input[0]);

    int m = stoi(first_multiple_input[1]);

    int k = stoi(first_multiple_input[2]);

    Maze maze(n,m);
        

    for (int n_itr = 0; n_itr < n; n_itr++) {
        string row;
        getline(cin, row);
        
        // Write your code here
        maze.addRow(std::move(row));
        if (maze.frogPosition == noPos) {
            size_t p = row.find("A");
            if (p != string::npos) {
                maze.setFrogPosition({n_itr, static_cast<int>(p)});
            }
        }
    }
    
    maze.setNumColumns(maze.rows[0].size());
    
    for (int k_itr = 0; k_itr < k; k_itr++) {
        string second_multiple_input_temp;
        getline(cin, second_multiple_input_temp);

        vector<string> second_multiple_input = split(rtrim(second_multiple_input_temp));

        int i1 = stoi(second_multiple_input[0]);

        int j1 = stoi(second_multiple_input[1]);

        int i2 = stoi(second_multiple_input[2]);

        int j2 = stoi(second_multiple_input[3]);

        // Write your code here
        maze.addTunnel({i1-1,j1-1}, {i2-1,j2-1});
    }

    // Write your code here
    maze.createVisitedMap();
    maze.createConnectionGraph();
    //maze.printConnectionGraph();
    cout << maze.computeProbability();

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}

vector<string> split(const string &str) {
    vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(" ", start)) != string::npos) {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}

//g++ -std=c++14 frog-in-maze.cpp -Wno-deprecated
