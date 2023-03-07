/*
Four Twenty Four Seven grids have been smooshified together within the 12-by-12 grid above.

Place numbers in some of the empty cells so that in total each of the four 7-by-7 outlined grids is a legal 
“Twenty Four Seven” grid.
Namely: each 7-by-7 grid’s interior should contain one 1, two 2’s, etc., up to seven 7’s.
Furthermore, each row and column within the 7-by-7’s must contain exactly 4 numbers which sum to 20.
Finally, the numbered cells must form a connected region, but every 2-by-2 subsquare in the completed grid must contain at least one empty cell.

Some numbers have been placed inside the grid. Additionally, some blue numbers have been placed outside
of the grids. A number outside the grid represents either the sum of the row or column it is facing, or the value of the first
 number it sees in that row or column.

Once completed, you can submit as your answer the product of the areas of the connected groups of orthogonally adjacent empty squares in the grid.

*/
#include <bits/stdc++.h>
#include <cstddef>
#include <cstring>
using namespace std;

constexpr short width = 12;
constexpr short height = 12;
constexpr short grid_size = width * height;

struct Grid {
    char values[grid_size];
    
    char available[8];
    char row_sum[height];
    char row_count[height];
    char col_sum[width];
    char col_count[width];
    void update_stats() {
        for (int i=0; i<8; i++) {
            available[i] = static_cast<char>(i);
        }
        for (int i=0; i<grid_size; i++) {
            char v = values[i];
            assert (v>=0 && v<=7);
            if (v > 0) {                
                available[v]--;
                if (available[v]<0) {
                    cerr << (int)v << ": " << (int)available[v] << endl;
                }
                assert (available[v] >= 0);
            }
        }
        memset(row_count,0,width);
        memset(row_sum,0,width);
        memset(col_sum,0,height);
        memset(col_count,0,height);
        for (int y=0; y<height; y++) {
            for (int x=0; x<width; x++) {
                char v = get(x,y);
                if (v>0) {
                    row_count[y]++;
                    row_sum[y] += v;
                    col_count[x]++;
                    col_sum[x] += v;
                }
            }
        }
    }
    Grid() {
        memset(values,0, grid_size);                
        update_stats();                
    }
    Grid(const Grid& g) {
        memcpy(values, g.values, grid_size);
        memcpy(available, g.available, 8);
        memcpy(row_count, g.row_count, width);
        memcpy(row_sum, g.row_sum, width);
        memcpy(col_sum, g.col_sum, height);
        memcpy(col_count, g.col_count, height);
    }


    Grid& operator=(const Grid& g) {
        memcpy(values, g.values, grid_size);
        memcpy(available, g.available, 8);
        memcpy(row_count, g.row_count, width);
        memcpy(row_sum, g.row_sum, width);
        memcpy(col_sum, g.col_sum, height);
        memcpy(col_count, g.col_count, height);
        return *this;
    }

    void set(int x, int y, int value) {
        assert (x>=0 && x < width);
        assert (y>=0 && y < height);
        assert (available[value] >= 1);
        //assert (get(x,y) == 0);
        values[x + y*width] = static_cast<char>(value);
        row_count[y]++;
        col_count[x]++;
        row_sum[y] += value;
        col_sum[x] += value;
        available[value]--;
    }
    char get(int x, int y) const {
        assert (x>=0 && x < width);
        assert (y>=0 && y < height);
        return values[x+y*width];
    }
    // void setInitialGrid() {
    //     memset(values,0,grid_size);
    //     char vals[] = 
    //     {0,0,0,0,0,0,0,0,0,0,0,0,
    //      0,0,0,1,0,0,0,0,0,6,5,0,
    //      0,0,0,0,0,3,0,0,0,0,6,0,
    //      0,4,0,0,0,0,0,0,7,0,0,0,
    //      0,0,0,0,2,0,0,0,0,0,0,7,
    //      0,0,6,0,0,0,0,0,3,7,0,0,
    //      0,0,0,0,0,0,0,0,0,0,0,0,
    //      0,0,0,0,0,0,0,0,0,0,0,0,
    //      0,0,0,7,0,5,0,0,0,0,0,0,
    //      0,5,0,0,0,7,0,0,0,0,0,0,
    //      0,6,7,0,0,0,0,0,0,0,0,0,
    //      0,0,0,0,6,0,0,0,0,0,0,0};
    //      memcpy(values, vals, grid_size);//*sizeof(int));
    //      update_stats();
    // }

   void setInitialGrid() {
        memset(values,0,grid_size);
        char vals[] = 
        {0,4,0,0,0,0,0,0,0,0,0,0,
         0,0,6,3,0,0,6,0,0,0,0,0,
         0,0,0,0,0,5,5,0,0,0,0,0,
         0,0,0,4,0,0,0,0,0,0,0,0,
         4,7,0,0,0,0,0,0,0,0,0,0,
         2,0,0,7,4,0,0,0,0,0,0,0,
         0,0,0,0,0,1,0,0,0,0,0,0,
         0,0,0,0,0,0,0,0,0,0,0,0,
         0,0,0,0,0,0,0,0,0,0,0,0,
         0,0,0,0,0,0,0,0,0,0,0,0,
         0,0,0,0,0,0,0,0,0,0,0,0,
         0,0,0,0,0,0,0,0,0,0,0,0};
         memcpy(values, vals, grid_size);//*sizeof(int));
         update_stats();
    }
//    void setInitialGrid() {
//         memset(values,0,grid_size);
//         char vals[] = 
//         {7,4,3,0,6,0,0,0,0,0,0,0,
//          0,0,6,3,5,0,6,0,0,0,0,0,
//          0,0,5,0,5,5,5,0,0,0,0,0,
//          0,3,6,4,0,0,7,0,0,0,0,0,
//          4,7,0,0,0,7,2,0,0,0,0,0,
//          2,0,0,7,4,7,0,0,0,0,0,0,
//          7,6,0,6,0,1,0,0,0,0,0,0,
//          0,0,0,0,0,0,0,0,0,0,0,0,
//          0,0,0,0,0,0,0,0,0,0,0,0,
//          0,0,0,0,0,0,0,0,0,0,0,0,
//          0,0,0,0,0,0,0,0,0,0,0,0,
//          0,0,0,0,0,0,0,0,0,0,0,0};
//          memcpy(values, vals, grid_size);//*sizeof(int));
//          update_stats();
//     }

    bool is7x7Solution(int x0, int y0, int x1, int y1, bool& possible, bool& pos_possible) {
        assert(x1-x0+1 == 7);
        assert(y1-y0+1 == 7);
        assert(x1>x0);
        assert(y1>y0);
        assert(x0 == 0 || x1==11);
        assert(y0 == 0 || y1==11);
        char counts[] = {0,0,0,0,0,0,0,0};
        int col_sums[] = {0,0,0,0,0,0,0};
        int col_counts[] = {0,0,0,0,0,0,0};
        for (int y=y0; y<=y1; y++) {
            int row_sum = 0;
            int row_count = 0;
            for (int x=x0; x<=x1; x++) {
                char c = get(x,y);
                col_sums[x] += c;
                col_counts[x] += (c>0)?1:0;
                row_sum += c;
                row_count += (c>0)?1:0;
                counts[c] += 1;                
            }            
            possible = (row_sum <= 20 && row_count <= 4);
            if (row_sum != 20) {                
                return false;
            }
            if (row_count != 4) {
                return false;
            }
        }
        for (int i=1;i<=7; i++) {
            possible = (counts[i] <= i);
            if (counts[i] != i) return false;
        }
        for (int i=0; i< 7; i++) {
            possible = (col_counts[i] <= 4 && col_sums[i] <= 20);
            if (col_counts[i] != 4) {
                return false;
            }
            if (col_sums[i] != 20) {
                return false;
            }
        }

        // check 2x2 subsquares
        for (int y=y0; y<=y1-1; y++) {
            for (int x=x0; x<=x1-1; x++) {
                int a = get(x,y);
                int b = get(x+1,y);
                int c = get(x,y+1);
                int d = get(x+1,y+1);
                if (a != 0 && b != 0 && c != 0 && d != 0) {
                    possible = false;
                    pos_possible = false;
                    return false;
                }
            }
        }
        return true;
    }
    bool operator==(const Grid& o) const {
        for (int i=0; i<grid_size; i++) {
            if (values[i] != o.values[i]) {
                return false;
            }
        }
        return true;
    }
};


namespace std {
    template<>
    struct hash<Grid> {        
        size_t operator()(const Grid& g) const {
            size_t sum=0;
            for (int i=0; i<grid_size; i++) {
                sum += (i+1)*g.values[i];
            }
            return sum;
        }
    };
}

ostream& operator<<(ostream& os, const Grid& g) {
    for (int r=0; r<height; r++) {
        for (int c=0; c<width; c++) {
            int v = g.get(c,r);
            if (v == 0) {
                os << '.';
            } else {
                os << v;
            }
        }
        os << " | " << static_cast<int>(g.row_count[r]) << " | " << static_cast<int>(g.row_sum[r]) << endl;
    }
    for (int i=0; i<width; i++) {
        os << "-";
    }
    os << endl;
    for (int i=0; i<width; i++) {
        os << static_cast<int>(g.col_count[i]);
    }
    os << endl << "Available: ";
    for (int i=0; i<8; i++) {
        os << (i) << ":" << static_cast<int>(g.available[i]) << " ";
    }
    os << endl;
    return os;
}

int main() {    
    Grid g;    
    g.setInitialGrid();    
        
    bool possible = true;
    bool pos_possible = true;
    cout << g << endl;    
    cout << "is Sol: " << g.is7x7Solution(0,0,6,6, possible, pos_possible) << "P:" << possible << endl;    
    
    vector<Grid> agenda;
    agenda.push_back(g);
    unordered_set<Grid> history;
    history.insert(g);
    // auto it = history.find(g);
    // cout << *it;
    // return 0;
    Grid result;
    int steps=0;
    int history_hits=0;
    int successors=0;
    vector<pair<int,int>> neighbors{{-1,0},{0,-1},{1,0},{0,1}};
    while (agenda.size()>0) {
        Grid current = agenda.back();
        agenda.pop_back();
        steps++;
        //for (int p = 0; p<grid_size; p++) {
        for (int x=0; x<=6; x++) {
            for (int y = 0; y<=6; y++) {
                // only expand the existing region in
                // order to stay connected
                if (current.row_count[y] >= 4) continue;
                if (current.col_count[x] >= 4) continue;
                if (current.row_sum[y] >= 20) continue;
                if (current.col_sum[y] >= 20) continue;
                if (current.get(x,y) != 0) {
                    for (auto pos : neighbors) {
                        int nx = x+pos.first;
                        int ny = y+pos.second;
                        if (nx<0 || nx >6 || ny < 0 || ny>6) {
                            break;
                        }
                        if (current.get(nx,ny) == 0) {
                            for (int i=1; i<=7; i++) {
                                if (current.available[i]==0) {
                                    continue;
                                }
                                if (current.row_sum[ny] > (20-i)) continue;
                                if (current.col_sum[nx] > (20-i)) continue;
                                successors++;
                                Grid succ(current);
                                //succ.values[p] = i;
                                succ.set(nx,ny,i);
                                if (history.find(succ) == history.end()) {
                                    history.insert(succ);
                                    bool possible = false;
                                    bool pos_possible = true;
                                    if (succ.is7x7Solution(0,0,6,6, possible, pos_possible)) {
                                        result = succ;
                                        goto finish;
                                    }
                                    if (!pos_possible) {
                                        break;
                                    }
                                    if (possible) {
                                        agenda.push_back(succ);                            
                                    }
                                } else {
                                    history_hits++;
                                }
                            }
                        }
                    }
                }    
            }
        }      
        // if (steps >= 3) break;
        if (steps%100000 == 0) {
            cout << current << endl;
            steps = 0;
        }
        if (steps%10000 == 0) {            
            cout << "Agenda: " << agenda.size() << " history hits " << history_hits << " succ " << successors << endl;
            history_hits = 0;
            successors=0;
        }

    }
    // for (const Grid& g : agenda) {
    //     cout << "***********" << endl;
    //     cout << g << endl;
    // }
finish:
    cout << result << endl;
    return 0;
}