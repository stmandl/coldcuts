#include <bits/stdc++.h>
using namespace std;
// use the Fenwick Tree implementation from CP4
#define LSOne(S) ((S) & -(S))
typedef long long ll;
typedef vector<ll> vll;
typedef vector<int> vi;
class FenwickTree {
private:
    vll ft;
public:
    FenwickTree(int m) {ft.assign(m+1, 0);}
    ll rsq(int j) {
	ll sum = 0;
	for (; j; j -= LSOne(j)) {
	    sum += ft[j];
	}
	return sum;
    }
    ll rsq(int i, int j) {return rsq(j) - rsq(i-1);}
    void update(int i, ll v) {
	for (; i<(int)ft.size(); i+= LSOne(i))
	    ft[i] += v;
    }
};

class LivePositions {
private:
    vi next_live;
    vi prev_live;
public:
    LivePositions(int num_pos) {
	next_live.assign(num_pos+1,0);
	prev_live.assign(num_pos+1,0);
	next_live[0] = -1;
	next_live[num_pos] = 1;
	for (ll i=1; i<num_pos;i++) {
	    next_live[i] = i+1;
	}
	prev_live[0] = -1;
	prev_live[1] = num_pos;
	for (ll i=num_pos; i>=2; i--) {
	    prev_live[i] = i-1;
	}	    
    }
    int clear_get_next(int pos) {
	ll next = next_live[pos];
	ll prev = prev_live[pos];
	next_live[prev] = next;
	prev_live[next] = prev;
	return next;
    }
	
};


int main()
{
    int n; cin >> n;
    vi ball_positions(n+1);
    for (int i=1; i<=n; i++) {
	int b; cin >> b;
	ball_positions[b]=i;
    }
    LivePositions live_positions(n);
    FenwickTree counter(n);
    int my_pos = 1;
    ll steps = 0;

    for (int i=1; i<=n; i++)
    {   
	int new_pos = ball_positions[i];
	if (new_pos != my_pos) {
	    //assert(counter.rsq(my_pos, my_pos) == 0);
	    /*
	     *  |3|2|1|
	     *  
	     */
	    int dist1 = -1;
	    int dist2 = -1;
	    if (new_pos < my_pos) {
		dist1 = my_pos - new_pos - counter.rsq(new_pos, my_pos);
		dist2 = n - my_pos + new_pos - counter.rsq(my_pos, n) - counter.rsq(1,new_pos);
	    } else if (my_pos < new_pos) {
		dist1 = new_pos - my_pos - counter.rsq(my_pos, new_pos);
		dist2 = my_pos + n - new_pos - counter.rsq(1, my_pos) - counter.rsq(new_pos, n);
	    } else {
		abort();
	    }
	    // rotate in the minimum distance direction
	    steps += std::min(dist1,dist2);
	}
	// drop the ball
	steps += 1;
	counter.update(new_pos, 1);
	my_pos = live_positions.clear_get_next(new_pos);
    }
    cout << steps;

    return 0;
}


// class Bitvector {
// private:
//     vll longlongs;
//     ll num_bits;
// public:
//     Bitvector(ll num_bits_)       
// 	{
// 	    num_bits = num_bits_;
// 	    int num_lls = num_bits / (sizeof(ll)*8);
// 	    bool needs_extra = (num_lls * sizeof(ll) * 8) != num_bits;
// 	    if (needs_extra) {num_lls++;}
// 	    longlongs.assign( num_lls, -1);
// 	    // clear the end
// 	    if (needs_extra) {
// 		//cout << "clearing the extra bits" << endl;
// 		int extra = num_lls * sizeof(ll) * 8 - num_bits;
// 		//cout << "clearing " << extra << " extra bits\n";
// 		for (int i=1; i<=extra; i++)
// 		{
// 		    //cout << std::hex << longlongs[longlongs.size()-1] << endl;
// 		    int j = sizeof(ll)*8-i;
// 		    //cout << "clear " << std::dec << j<<":" << std::hex << ~(((ll)1)<<j) << endl;
// 		    longlongs[longlongs.size()-1] &= ~(((ll)1)<<j);
// 		}

// 	    }
// 	}
//     void print() {
// 	for (int i=0; i<longlongs.size(); i++) {
// 	    cout << std::hex << longlongs[i];
// 	}
// 	cout << endl;	
//     }
//     inline void clear(ll num) {
// 	ll pos = num / (sizeof(ll)*8);
// 	ll i = num - pos*sizeof(ll)*8;
// 	longlongs[pos] &= ~(((ll)1)<<i);
//     }
//     inline int find_next_live_pos(ll p) {
// 	ll longlongssize = longlongs.size();
// 	int start_llpos = p / (sizeof(ll)*8);
// 	int start_bitpos = p - start_llpos * sizeof(ll) * 8;
// 	ll current = longlongs[start_llpos];
// 	__builtin_prefetch(&(longlongs[0])+((start_llpos + 1) % longlongssize), 0, 0);
// 	if ((((ll)1)<<start_bitpos) & current) {
// 	    return p;
// 	}
// 	if (start_bitpos > 0) {
// 	    ll mask = ~((((ll)1) << (start_bitpos)) -1);
// 	    //cout << ">" << std::hex << current << "&=" << mask;	
// 	    current &= mask;
// 	}
// 	//cout << "=" << current << endl;
// 	int llpos = start_llpos;

// 	for(;;) {
// 	    int offs = __builtin_ffsl(current);
// 	    if (offs != 0) {
// 		return llpos * sizeof(ll) * 8 + offs - 1;
// 	    }
// 	    llpos = (llpos + 1) % longlongssize;
// 	    current = longlongs[llpos];
// 	    __builtin_prefetch(&(longlongs[0])+((llpos + 1) % longlongssize), 0, 0);
// 	    if (llpos == start_llpos) {
// 		// ok, we've gone full circle and found no bits
// 		// so we have to check where we started but only up to start_bitpos
// 		if (start_bitpos > 0) {
// 		    ll mask = (((ll)1) << (start_bitpos)) - 1;
// 		    current &= mask;
// 		    int offs = __builtin_ffs(current);
// 		    if (offs != 0) {
// 			return llpos * sizeof(ll) * 8 + offs - 1;
// 		    }		    
// 		}
// 		return -1;
// 	    }
// 	}
//     }
    
// };

// int main()
// {
//     int n; cin >> n;

//     vi ball_positions(n+1);
//     for (int i=1; i<=n; i++) {
// 	int b; cin >> b;
// 	ball_positions[b]=i;
//     }
//     Bitvector live_positions(n);
//     FenwickTree counter(n);
//     int my_pos = 1;
//     ll steps = 0;

//     for (int i=1; i<=n; i++)
//     {   
// 	int new_pos = ball_positions[i];
// 	if (new_pos != my_pos) {
// 	    assert(counter.rsq(my_pos, my_pos) == 0);
// 	    /*
// 	     *  |3|2|1|
// 	     *  
// 	     */
// 	    int dist1 = -1;
// 	    int dist2 = -1;
// 	    if (new_pos < my_pos) {
// 		dist1 = my_pos - new_pos - counter.rsq(new_pos, my_pos);
// 		dist2 = n - my_pos + new_pos - counter.rsq(my_pos, n) - counter.rsq(1,new_pos);
// 	    } else if (my_pos < new_pos) {
// 		dist1 = new_pos - my_pos - counter.rsq(my_pos, new_pos);
// 		dist2 = my_pos + n - new_pos - counter.rsq(1, my_pos) - counter.rsq(new_pos, n);
// 	    } else {
// 		abort();
// 	    }
// 	    // rotate in the minimum distance direction
// 	    steps += std::min(dist1,dist2);
// 	}
// 	// drop the ball
// 	steps += 1;
// 	counter.update(new_pos, 1);
// 	live_positions.clear(new_pos-1);
// 	if (i < n) {
// 	    //cerr << "old my_pos: " << my_pos << " new_pos= " << new_pos;
// 	    my_pos = live_positions.find_next_live_pos(new_pos-1); 
// 	    assert(my_pos != -1);
// 	    my_pos += 1;
// 	}
//     }
//     cout << steps;

//     return 0;
// }
