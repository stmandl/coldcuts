#include <bits/stdc++.h>
using namespace std;

class range_counter
{
private:
    vector<int> counts;
public:
    range_counter(int size)
	: counts(0, n)
	{}
    int add(int pos) {
	assert(counts[pos] == 0);
	counts[pos] += 1;
    }
    int count(int from, int below) {
	int c = 0;
	for (size_t i = from; i<below; i++) {
	    c += count[i];
	}
    }
};

int main()
{
    int n;
    cin >> n;
    vector<int> balls;
    balls.reserve(n);
    vector<int> ball_positions(0, n+1);
    for (int i=0; i<n; i++)
	{
	    int b;
	    cin >> b;
	    b = b -1; // make everything zero-based
	    balls.push_back(b);
	    ball_positions[b]=i;
	}
	
    unsigned int my_pos = 0;
    unsigned int size = n;
    int sum_size =0;
    for (int i=0; i<n; i++)
	{
	    int dist1 = (ball_positions[i] + size - my_pos) % size;
	    int dist2 = (my_pos - ball_positions[i] + size) % size;
	    for (int j=0; j<size; j++)
		{
		    if (ball_positions[j] > my_pos) {
			ball_positions[j] -= 1;
		    }
		}
	    if (dist1 < dist2) {
		sum_size += dist1;
 			
	    } else {
		sum_size += dist2;
	    }
	    my_pos = ball_positions[i];
	}
    cerr << "bs= " << balls.size();
    assert(balls.size() == n);

}
