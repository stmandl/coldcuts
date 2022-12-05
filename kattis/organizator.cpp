/*
 * Task:
 * N
 * n1 .. n_N
 *
 * find subset S of the n_i which maximizes lcd(S) * |S| with |S|>=2
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vll;
typedef vector<int> vi;

ll compute_gcd(ll a, ll b) {
    for(;;) {
	if (b==0)
	    return a;
	ll tmp = b;
	b = a%b;
	a = tmp;
    }
    abort();
}

class Bitvector {
    friend std::hash<Bitvector>;
private:
    vll longlongs;
    ll num_bits;
public:
    bool operator==(const Bitvector& o) const {
        return o.num_bits == num_bits && o.longlongs == longlongs;
    }
    Bitvector(ll num_bits_) {
	num_bits = num_bits_;
	int num_lls = num_bits / (sizeof(ll)*8);
	bool needs_extra = (num_lls * sizeof(ll) * 8) != num_bits;
	if (needs_extra) {num_lls++;}
	longlongs.assign( num_lls, -1);
	// clear the end
	if (needs_extra) {
	    //cout << "clearing the extra bits" << endl;
	    int extra = num_lls * sizeof(ll) * 8 - num_bits;
	    //cout << "clearing " << extra << " extra bits\n";
	    for (int i=1; i<=extra; i++)
	    {
		//cout << std::hex << longlongs[longlongs.size()-1] << endl;
		int j = sizeof(ll)*8-i;
		//cout << "clear " << std::dec << j<<":" << std::hex << ~(((ll)1)<<j) << endl;
		longlongs[longlongs.size()-1] &= ~(((ll)1)<<j);
	    }	    
	}
    }
    void print() {
	for (int i=0; i<longlongs.size(); i++) {
	    cout << std::hex << longlongs[i];
	}
	cout << endl;	
    }
    inline void clear(ll num) {
	ll pos = num / (sizeof(ll)*8);
	ll i = num - pos*sizeof(ll)*8;
	longlongs[pos] &= ~(((ll)1)<<i);
    }
    inline int find_next_live_pos(ll p) {
	cerr << "fnlp-1: " << dec << p << endl;
	ll longlongssize = longlongs.size();
	cerr << "fnlp-2: " << dec << longlongssize << endl;
	int start_llpos = p / (sizeof(ll)*8);
	cerr << "fnlp-3: " << dec << start_llpos << endl;
	int start_bitpos = p - start_llpos * sizeof(ll) * 8;
	cerr << "fnlp-4: " << dec << start_bitpos << endl;
	ll current = longlongs[start_llpos];
	cerr << "fnlp-5: " << hex << current << endl;
	__builtin_prefetch(&(longlongs[0])+((start_llpos + 1) % longlongssize), 0, 0);
	if ((((ll)1)<<start_bitpos) & current) {
	    return p;
	}
	if (start_bitpos > 0) {
	    ll mask = ~((((ll)1) << (start_bitpos)) -1);
	    current &= mask;
	}
	int llpos = start_llpos;

	for(;;) {
	    int offs = __builtin_ffsl(current);
	    if (offs != 0) {
		return llpos * sizeof(ll) * 8 + offs - 1;
	    }
	    llpos = (llpos + 1) % longlongssize;
	    current = longlongs[llpos];
	    __builtin_prefetch(&(longlongs[0])+((llpos + 1) % longlongssize), 0, 0);
	    if (llpos == start_llpos) {
		// ok, we've gone full circle and found no bits
		// so we have to check where we started but only up to start_bitpos
		if (start_bitpos > 0) {
		    ll mask = (((ll)1) << (start_bitpos)) - 1;
		    current &= mask;
		    int offs = __builtin_ffs(current);
		    if (offs != 0) {
			return llpos * sizeof(ll) * 8 + offs - 1;
		    }		    
		}
		return -1;
	    }
	}
    }    
};


namespace std {
template <>
struct hash<Bitvector> {
  auto operator()(const Bitvector &v) const -> size_t {
      ll m = 0;
      for (ll v : v.longlongs) {
	  m += v;
      }
      return m;
  }
};
}  

class State {
public:
    Bitvector bv;
    ll score;
    ll potential_score;
    ll gcd;
    ll size;
    State(const vll& team_sizes, int add_position) : bv(team_sizes.size()), gcd(team_sizes[add_position]), size(1) {
	bv.clear(add_position);
	score = gcd * size;
	potential_score = gcd * team_sizes.size();	
    }
    State(const vll& team_sizes, const State& parent, int add_position)
	: bv(parent.bv), gcd(compute_gcd(parent.gcd, team_sizes[add_position])), size(parent.size + 1) {
	potential_score = gcd * team_sizes.size();
	bv.clear(add_position);
    }
    bool operator==(const State& o) const {
        return o.bv == bv;
    }

};


namespace std {
template <>
struct hash<State> {
  auto operator()(const State &v) const -> size_t {
      return std::hash<Bitvector>{}(v.bv);
  }
};
}  


int main()
{
    ll N;
    cin >> N;
    vll sizes;
    for (ll i=1; i<=N; i++)
    {
	ll size;
	cin >> size;
	sizes.push_back(size);
    }


    vector<State> agenda;
    ll best_score = -1;
    for (int i=0; i<N; i++) {
	agenda.emplace_back(State(sizes, i));
    }
    unordered_set<State> history;
    
    while (agenda.size() > 0) {
	cout << agenda.size() << endl;
	State& current = agenda.back();
	if (current.potential_score > best_score)
	{
	    if (current.score > best_score && current.size > 1) {
		best_score = current.score;
	    }
	    // consider children
	    ll pos = -1;
	    for(;;) {
		cerr << "p:"<< dec << pos<< endl;
		cerr << "p:"<< dec << pos+1<< endl;
		int pos = current.bv.find_next_live_pos(pos+1);
		if (pos == -1) {
		    break;
		}
		State new_state(sizes, current, pos);
		if (history.find(new_state) == history.end())
		{
		    agenda.push_back(new_state);
		    history.insert(current);
		}
	    }
	}
	agenda.pop_back();
    }

    cout << best_score;
    return 0;
}
