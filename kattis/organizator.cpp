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

ll compute_gcd(ll a, ll b)
{
	for (;;)
	{
		if (b == 0)
			return a;
		ll tmp = b;
		b = a % b;
		a = tmp;
	}
	abort();
}

class Bitvector
{
	friend std::hash<Bitvector>;

private:
	vll longlongs;
	ll num_bits;

public:
	bool operator==(const Bitvector &o) const
	{
		return o.num_bits == num_bits && o.longlongs == longlongs;
	}
	Bitvector(const Bitvector &other)
		: longlongs(other.longlongs),
		  num_bits(other.num_bits)
	{
		cerr << "Copied a bitvector!" << endl;
	}
	Bitvector(ll num_bits_)
	{
		num_bits = num_bits_;
		assert(num_bits > 0);
		int num_lls = num_bits / (sizeof(ll) * 8);
		bool needs_extra = (num_lls * sizeof(ll) * 8) != num_bits;
		if (needs_extra)
		{
			num_lls++;
		}
		longlongs.assign(num_lls, -1);
		// clear the end
		if (needs_extra)
		{
			// cout << "clearing the extra bits" << endl;
			int extra = num_lls * sizeof(ll) * 8 - num_bits;
			// cout << "clearing " << extra << " extra bits\n";
			for (int i = 1; i <= extra; i++)
			{
				// cout << std::hex << longlongs[longlongs.size()-1] << endl;
				int j = sizeof(ll) * 8 - i;
				// cout << "clear " << std::dec << j<<":" << std::hex << ~(((ll)1)<<j) << endl;
				longlongs[longlongs.size() - 1] &= ~(((ll)1) << j);
			}
		}
	}
	void print()
	{
		for (int i = 0; i < longlongs.size(); i++)
		{
			cout << std::hex << longlongs[i];
		}
		cout << endl;
	}
	inline void clear(ll num)
	{
		ll pos = num / (sizeof(ll) * 8);
		ll i = num - pos * sizeof(ll) * 8;
		longlongs[pos] &= ~(((ll)1) << i);
	}
	inline int getBit(ll num) const
	{
		ll pos = num / (sizeof(ll) * 8);
		ll i = num - pos * sizeof(ll) * 8;
		return longlongs[pos] & (((ll)1) << i);
	}
	// inline int find_next_live_pos(ll p)
	// {
	// 	cerr << "FNLP (" << hex << this << ")" << endl;
	// 	cerr << "fnlp-1: " << dec << p << endl;
	// 	ll longlongssize = longlongs.size();
	// 	cerr << "fnlp-2: vector-size: " << dec << longlongssize << endl;
	// 	int start_llpos = p / (sizeof(ll) * 8);
	// 	cerr << "fnlp-3: " << dec << start_llpos << endl;
	// 	int start_bitpos = p - start_llpos * sizeof(ll) * 8;
	// 	cerr << "fnlp-4: " << dec << start_bitpos << endl;
	// 	ll current = longlongs[start_llpos];
	// 	cerr << "fnlp-5: " << hex << current << endl;
	// 	__builtin_prefetch(&(longlongs[0]) + ((start_llpos + 1) % longlongssize), 0, 0);
	// 	if ((((ll)1) << start_bitpos) & current)
	// 	{
	// 		cerr << "vector_size after1: " << longlongs.size() << endl;
	// 		return p;
	// 	}
	// 	if (start_bitpos > 0)
	// 	{
	// 		ll mask = ~((((ll)1) << (start_bitpos)) - 1);
	// 		current &= mask;
	// 	}
	// 	int llpos = start_llpos;

	// 	for (;;)
	// 	{
	// 		int offs = __builtin_ffsl(current);
	// 		if (offs != 0)
	// 		{
	// 			cerr << "vector_size after2: " << longlongs.size() << endl;
	// 			return llpos * sizeof(ll) * 8 + offs - 1;
	// 		}
	// 		llpos = (llpos + 1) % longlongssize;
	// 		current = longlongs[llpos];
	// 		__builtin_prefetch(&(longlongs[0]) + ((llpos + 1) % longlongssize), 0, 0);
	// 		if (llpos == start_llpos)
	// 		{
	// 			// ok, we've gone full circle and found no bits
	// 			// so we have to check where we started but only up to start_bitpos
	// 			if (start_bitpos > 0)
	// 			{
	// 				ll mask = (((ll)1) << (start_bitpos)) - 1;
	// 				current &= mask;
	// 				int offs = __builtin_ffs(current);
	// 				if (offs != 0)
	// 				{
	// 					cerr << "vector_size after3: " << longlongs.size() << endl;
	// 					return llpos * sizeof(ll) * 8 + offs - 1;
	// 				}
	// 			}
	// 			return -1;
	// 		}
	// 	}
	// }
	inline int find_next_live_pos(ll p)
	{
		if (p >= num_bits)
		{
			return -1;
		}
		//cerr << "FNLP (" << hex << this << ")" << endl;
		//cerr << "p=" << dec << p << endl;
		ll longlongssize = longlongs.size();
		//cerr << "vector-size=" << dec << longlongssize << endl;
		int start_llpos = p / (sizeof(ll) * 8);
		//cerr << "start_llpos=" << dec << start_llpos << endl;
		int start_bitpos = p - start_llpos * sizeof(ll) * 8;
		//cerr << "start_bitpos=" << dec << start_bitpos << endl;
		ll current = longlongs[start_llpos];
		//cerr << "current word= " << hex << current << endl;
		//__builtin_prefetch(&(longlongs[0]) + ((start_llpos + 1) % longlongssize), 0, 0);
		if ((((ll)1) << start_bitpos) & current)
		{
			//cerr << "vector_size after1: " << longlongs.size() << endl;
			return p;
		}

		if (start_bitpos > 0)
		{
			ll mask = ~((((ll)1) << (start_bitpos)) - 1);
			current &= mask;
		}

		//cerr << "current before loop: " << current << endl;
		int llpos = start_llpos;

		for (;;)
		{
			int offs = __builtin_ffsl(current);
			//cerr << "offs=" << dec << offs << endl;
			if (offs != 0)
			{
				//cerr << "vector_size after2: " << longlongs.size() << endl;
				return llpos * sizeof(ll) * 8 + offs - 1;
			}
			llpos = (llpos + 1) % longlongssize;
			//cerr << "llpos = " << llpos << endl;
			current = longlongs[llpos];
			//cerr << "current = " << hex << current << dec << endl;
			//__builtin_prefetch(&(longlongs[0]) + ((llpos + 1) % longlongssize), 0, 0);
			if (llpos == start_llpos)
			{
				//cerr << "full circle" << endl;
				// ok, we've gone full circle and found no bits
				// so we have to check where we started but only up to start_bitpos
				// if (start_bitpos > 0)
				//{
				ll mask = (((ll)1) << (start_bitpos)) - 1;
				current &= mask;
				//cerr << "mask=" << hex << mask << " masked current = " << current << " start_bitpos=" << dec << start_bitpos << endl;
				int offs = __builtin_ffsl(current);
				if (offs != 0)
				{
					//cerr << "vector_size after3: " << longlongs.size() << endl;
					return llpos * sizeof(ll) * 8 + offs - 1;
				}
				else
				{
					//}
					return -1;
				}
			}
		}
	}
}  __attribute__ ((aligned (sizeof(ll))));

void bitvector_test()
{
	Bitvector b1(1);
	assert(b1.find_next_live_pos(0) == 0);
	assert(b1.find_next_live_pos(1) == -1);
	Bitvector b2(2);
	assert(b2.find_next_live_pos(0) == 0);
	assert(b2.find_next_live_pos(1) == 1);
	b2.clear(1);
	assert(b2.find_next_live_pos(1) == 0);
	b2.clear(0);
	assert(b2.find_next_live_pos(1) == -1);

	Bitvector b3(65);
	for (int i = 0; i < 65; i++)
	{
		assert(b3.find_next_live_pos(i) == i);
		b3.clear(i);
	}
	assert(b3.find_next_live_pos(0) == -1);

	Bitvector b4(65);
	for (int i = 0; i < 65; i++)
	{
		assert(b4.find_next_live_pos(0) == i);
		b4.clear(i);
	}
	assert(b3.find_next_live_pos(0) == -1);

	for (int i = 0; i < 100; i++)
	{
		int size = rand() % 100000 + 10;
		//int size = rand() % 5;
		int start_pos = rand() % size;
		Bitvector b5(size);
		for (int j = 0; j < size; j++)
		{
			int nlp = b5.find_next_live_pos(start_pos);
			if (nlp != ((start_pos + j) % size))
			{
				cerr << "FAIL: nlp: " << dec << nlp << " sp= " << start_pos << " size= " << size << " j=" << j << endl;
			}
			assert(nlp == ((start_pos + j) % size));
			b5.clear((start_pos + j) % size);
		}
		assert(b5.find_next_live_pos(start_pos) == -1);
	}
}

namespace std
{
	template <>
	struct hash<Bitvector>
	{
		auto operator()(const Bitvector &v) const -> size_t
		{
			ll m = 0;
			for (ll v : v.longlongs)
			{
				m += v;
			}
			return m;
		}
	};
}

class State
{
public:
	Bitvector bv;
	ll score;
	ll potential_score;
	ll gcd;
	ll size;
	State(const vll &team_sizes, int add_position) : bv(team_sizes.size()), gcd(team_sizes[add_position]), size(1)
	{
		bv.clear(add_position);
		score = gcd * size;
		potential_score = gcd * team_sizes.size();
	}
	State(const vll &team_sizes, const State &parent, int add_position)
		: bv(parent.bv), gcd(compute_gcd(parent.gcd, team_sizes[add_position])), size(parent.size + 1)
	{
		potential_score = gcd * team_sizes.size();
		score = gcd * size;
		bv.clear(add_position);
	}
	bool operator==(const State &o) const
	{
		return o.bv == bv;
	}


} __attribute__ ((aligned (sizeof(ll))));

size_t the_team_sizes=-1;

std::ostream& operator <<(std::ostream& s, const State& st) {
	s << "[L:" << st.size << "|Sc:" << st.score << "|P:" << st.potential_score << "GCD:" << st.gcd << "|Bits:";
	for (int i=0; i<the_team_sizes;i++)
	{
		s << st.bv.getBit(i);
	}
	s << "]";
	return s;
}

namespace std
{
	template <>
	struct hash<State>
	{
		auto operator()(const State &v) const -> size_t
		{
			return std::hash<Bitvector>{}(v.bv);
		}
	};
}

int main()
{

	//bitvector_test();
	//return 0;

	ll N;
	cin >> N;
	vll sizes;
	for (ll i = 1; i <= N; i++)
	{
		ll size;
		cin >> size;
		sizes.push_back(size);
	}

	the_team_sizes = N;

	vector<State> agenda;
	ll best_score = -1;
	for (int i = 0; i < N; i++)
	{
		agenda.emplace_back(State(sizes, i));
	}
	unordered_set<State> history;

	while (agenda.size() > 0)
	{
		cout << agenda.size() << endl;
		State current = agenda.back();
		cerr << "current: " << current << endl;
		agenda.pop_back();
		history.insert(current);
		if (current.potential_score > best_score)
		{
			if (current.score > best_score && current.size > 1)
			{
				best_score = current.score;
				cerr << "Updated best_score to " << best_score << " from size set=" << current.size << endl;
			}
			// consider children
			ll pos = 0;
			cerr << "creating successor state" << endl;
			for (;;)
			{
				cerr << "p:" << dec << pos << endl;
				cerr << "p:" << dec << pos + 1 << endl;
				int old_pos = pos;
				pos = current.bv.find_next_live_pos(pos);
				cerr << "Pos (after):" << pos << endl;
				if (pos == -1)
				{
					break;
				}
				if (old_pos != -1) {
					current.bv.clear(pos);
				}				
				State new_state(sizes, current, pos);
				if (history.find(new_state) == history.end())
				{
					agenda.push_back(new_state);
				}
			}
			cerr << "done." << endl;
		} else{
			cerr << " .. dropped" << endl;
		}		
		cout << "AGENDA SIZE=" << agenda.size() << endl;
	}

	cout << "RESULT: " << best_score << endl;
	return 0;
}
