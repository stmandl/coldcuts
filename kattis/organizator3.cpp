/*
 * Task:
 * N
 * n1 .. n_N
 *
 * find subset S of the n_i which maximizes lcd(S) * |S| with |S|>=2
 */
#include <bits/stdc++.h>
#include <chrono>
using namespace std::chrono;
using namespace std;
typedef long long ll;
typedef vector<ll> vll;
typedef vector<int> vi;

using fmap = unordered_map<int, int>;

class Bitvector
{
	friend std::hash<Bitvector>;

private:
	vll longlongs;
	

public:
	ll num_bits;
	bool operator==(const Bitvector &o) const
	{
		return o.num_bits == num_bits && o.longlongs == longlongs;
	}
	Bitvector(const Bitvector &other)
		: longlongs(other.longlongs),
		  num_bits(other.num_bits)
	{
		;//cerr << "Copied a bitvector!" << endl;
	}
	Bitvector(const Bitvector &&other)
		: longlongs(std::move(other.longlongs)),
		  num_bits(std::move(other.num_bits))
	{
		//cerr << "Moved a bitvector!" << endl;
	}
	Bitvector & operator=( Bitvector && ) = default;	
	
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
	// void print()
	// {
	// 	for (int i = 0; i < longlongs.size(); i++)
	// 	{
	// 		cout << std::hex << longlongs[i];
	// 	}
	// 	cout << endl;
	// }
	inline void clear(ll num)
	{
		ll pos = num / (sizeof(ll) * 8);
		ll i = num - pos * sizeof(ll) * 8;
		longlongs[pos] &= ~(((ll)1) << i);
	}
	inline bool getBit(ll num) const
	{
		ll pos = num / (sizeof(ll) * 8);
		ll i = num - pos * sizeof(ll) * 8;
		return longlongs[pos] & (((ll)1) << i);
	}

	inline int find_next_live_pos(ll p) const
	{
		if (p >= num_bits)
		{
			return -1;
		}
		// cerr << "FNLP (" << hex << this << ")" << endl;
		// cerr << "p=" << dec << p << endl;
		ll longlongssize = longlongs.size();
		// cerr << "vector-size=" << dec << longlongssize << endl;
		int start_llpos = p / (sizeof(ll) * 8);
		// cerr << "start_llpos=" << dec << start_llpos << endl;
		int start_bitpos = p - start_llpos * sizeof(ll) * 8;
		// cerr << "start_bitpos=" << dec << start_bitpos << endl;
		ll current = longlongs[start_llpos];
		// cerr << "current word= " << hex << current << endl;
		//__builtin_prefetch(&(longlongs[0]) + ((start_llpos + 1) % longlongssize), 0, 0);
		if ((((ll)1) << start_bitpos) & current)
		{
			// cerr << "vector_size after1: " << longlongs.size() << endl;
			return p;
		}

		if (start_bitpos > 0)
		{
			ll mask = ~((((ll)1) << (start_bitpos)) - 1);
			current &= mask;
		}

		// cerr << "current before loop: " << current << endl;
		int llpos = start_llpos;

		for (;;)
		{
			int offs = __builtin_ffsl(current);
			// cerr << "offs=" << dec << offs << endl;
			if (offs != 0)
			{
				// cerr << "vector_size after2: " << longlongs.size() << endl;
				return llpos * sizeof(ll) * 8 + offs - 1;
			}
			llpos = (llpos + 1) % longlongssize;
			// cerr << "llpos = " << llpos << endl;
			current = longlongs[llpos];
			// cerr << "current = " << hex << current << dec << endl;
			//__builtin_prefetch(&(longlongs[0]) + ((llpos + 1) % longlongssize), 0, 0);
			if (llpos == start_llpos)
			{
				// cerr << "full circle" << endl;
				//  ok, we've gone full circle and found no bits
				//  so we have to check where we started but only up to start_bitpos
				//  if (start_bitpos > 0)
				//{
				ll mask = (((ll)1) << (start_bitpos)) - 1;
				current &= mask;
				// cerr << "mask=" << hex << mask << " masked current = " << current << " start_bitpos=" << dec << start_bitpos << endl;
				int offs = __builtin_ffsl(current);
				if (offs != 0)
				{
					// cerr << "vector_size after3: " << longlongs.size() << endl;
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
} __attribute__((aligned(sizeof(ll))));

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

// prime numbers
ll _sieve_size;
bitset<2000010> bs;
vll p;

void sieve(ll upperbound)
{
	_sieve_size = upperbound + 1;
	bs.set();
	bs[0] = bs[1] = 0;
	for (ll i=2; i<_sieve_size; ++i)
		if (bs[i]) {
			// cross out multiplues of i starting from i*i
			for (ll j = i*i; j<_sieve_size; j+=i)
				bs[j] = 0;
			p.push_back(i);
		}
}

bool isPrime(ll N)
{
	if (N<_sieve_size) return bs[N];
	abort();
}

void update_stat(ll value, ll new_f, fmap& freqs_stat, bool max_mode) {
	auto f = freqs_stat.find(value);
	if (f == freqs_stat.end()
		|| (max_mode && f->second < new_f)
		|| ((!max_mode) && f->second > new_f)) {
		freqs_stat.insert_or_assign(value, new_f);
	} 
}

void primeFactors(ll N, fmap& freqs,
					fmap& pmin_freqs, fmap& pmax_freqs) {	
	for (int i=0; (i < (int)p.size()) && (p[i]*p[i] <= N); ++i)
	{		
		int c = 0;
		while (N%p[i] == 0) {			
			N /= p[i];
			c+=1;
		}
		if (c>0) {
			update_stat(p[i], c, pmin_freqs, false);
			update_stat(p[i], c, pmax_freqs, true);
			freqs.insert(make_pair(p[i],c));
		}
	}
	if (N != 1) {
		update_stat(N, 1, pmin_freqs, false);
		update_stat(N, 1, pmax_freqs, true);
		freqs.insert(make_pair(N,1));
	}
}

void print_primefactors(const vll& sizes, const vector<fmap>& freqs)
{
	for (int i=0; i<sizes.size(); i++) {
		cout << sizes[i] << ": ";
		for (auto& f : freqs[i]) {
			cout << "(" << f.first << "^" << f.second << ")";
		}
		cout << endl;
	}
}

void print_pfreqs(const fmap& freqs, bool end_line=true, std::ostream &s = cout)
{
	for (auto& f : freqs) {
		cout << "(" << f.first << ":" << f.second << ")";
	}
	if (end_line) {
		cout << endl;
	}
}

void print_vll(std::ostream&s, const vll& v) {
	for (auto l : v) {
		s << l << ",";
	}	
}

std::ostream &operator<<(std::ostream &s, const Bitvector &b)
{
	for (int i = 0; i < b.num_bits; i++)
	{
		s << b.getBit(i);
	}
	return s;
}

ll eval_time = 0;
ll evaluate(ll factors, const vector<ll>& teams, ll num_actions, Bitvector& eval_positions) {
	auto start = high_resolution_clock::now();
	ll res=0;
	ll num_teams_covered = 0;
	
	ll pos = 0;
	
	for (;;) {
		//cout << "BS:" << eval_positions << endl;
		//cout << "pos:" << pos << endl;
		ll new_pos = eval_positions.find_next_live_pos(pos);
		if (new_pos == -1 || new_pos < pos ) {
			break;
		}
		pos = new_pos+1;
		ll team = teams[pos];
		ll g = team / factors;
		//cout << "gcd(" << factors << "," << team << ")="  << g << endl;
		if ((g * factors == team)) {
			res+=factors;
			num_teams_covered++;
		} else {
			eval_positions.clear(pos);
		}
	}
	if (num_teams_covered < 2) {
		res = 0;
	}
	//cout << "num_teams_covered= " << num_teams_covered << " res=" << res << endl;
	auto stop = high_resolution_clock::now();
	eval_time += duration_cast<nanoseconds>(stop - start).count();
	return res;
};

struct State {	
	friend std::hash<State>;
	ll applied_actions;
	vll remaining_actions;
	Bitvector eval_positions;
	ll score;
	ll num_actions;
	State(const vll& remaining_actions_, ll num_teams)
	: applied_actions(1), remaining_actions(remaining_actions_), eval_positions(num_teams), score(0), num_actions(0)
	{		
	}
	State(ll applied_actions_, const vll& remaining_actions_, ll num_actions_, ll score_, Bitvector& eval_positions_) :
    	applied_actions(applied_actions_), remaining_actions(remaining_actions_), eval_positions(std::move(eval_positions_)), num_actions(num_actions_), score(score_)
	{
		
	}
	bool operator==(const State &o) const 
	{
		return applied_actions == o.applied_actions && remaining_actions == o.remaining_actions;
	}
	friend bool operator<(const State &a, const State &b) 
	{
		return a.score < b.score;
	}
};

namespace std
{
	template <>
	struct hash<State>
	{
		auto operator()(const State &v) const -> size_t
		{
			return v.applied_actions;
		}
	};
}

struct StateCmp
{
	constexpr bool operator()(const State& a, const State&b) const {
		return a.score < b.score;
	}
};

std::ostream &operator<<(std::ostream &s, const State &b)
{
	s << "[Sc:" << dec << b.score << "," << b.applied_actions;
	s << "||";
	print_vll(s, b.remaining_actions);
	s << "]";
	return s;
}

int main() {
	ll max_prime = ll(sqrt(2'000'000))+1;
	// cout << "BP=" << max_prime << endl;
	sieve(max_prime);
	
	// read input
	ll N;
	cin >> N;
	vll sizes;
	for (ll i = 1; i <= N; i++)
	{
		ll size;
		cin >> size;
		sizes.push_back(size);
	}

	// factorize
	vector<fmap> pfreqs;
	fmap pmin_freqs;
	fmap pmax_freqs;
	for (ll i : sizes) {
		pfreqs.emplace_back(fmap{});
		fmap& current = pfreqs.back();
		primeFactors(i, current, pmin_freqs, pmax_freqs);
	}

	// print_primefactors(sizes, pfreqs);
	// cout << "Min: ";print_pfreqs(pmin_freqs);
	// cout << "Max: ";print_pfreqs(pmax_freqs);

	vll my_primes;
	for (const auto& f : pmax_freqs) {
		for (int i=0; i<f.second; i++) {
			if (f.first > 1) {
				my_primes.push_back(f.first);
			}
		}
	}
	cout << "num primes:" << my_primes.size() << endl;

	vector<State> agenda;
	ll best_score = -1;
	// initial state
	agenda.emplace_back(State(my_primes, sizes.size()));

	//priority_queue<State, vector<State>, StateCmp> agenda(agenda_raw.begin(), agenda_raw.end());
	unordered_set<State> history;

	ll search_space = 0;
	while (agenda.size() > 0)
	{
		// cout << "****** AGENDA (" << agenda.size() << ") *****" << endl;
		// for (const auto& ai :  agenda) {
		// 	cout << ai << endl;
		// }
		// cout << "********************" << endl;
		std::pop_heap(agenda.begin(), agenda.end());
		State current = agenda.back();
		agenda.pop_back();

		search_space++;
		// cerr << ">> current: " << current << " with " << current.remaining_actions.size() << " remaining actions" << endl;
		
		//cout << "AS=" << agenda.size() << endl;
		history.insert(current);
//		if (current.potential_score > best_score)
//		{
		if (current.score > best_score)
		{
			best_score = current.score;
			// cerr << "Updated best_score to " << best_score << " from size set=" << current.size << endl;
		}
		std::unordered_set<ll> unsuccessful;			
		for (int i=0; i<current.remaining_actions.size(); i++) {
			
			ll current_action = current.remaining_actions[i];
			// if (unsuccessful.find(current_action) != unsuccessful.end()) {
			// 	continue;
			// }			
			// State child(current.applied_actions, new_remaining_actions, current_action, sizes, current.num_actions+1);

			ll child_applied_actions = current.applied_actions * current_action;
			ll child_num_actions = current.num_actions+1;
			Bitvector new_eval_positions = current.eval_positions;
			ll new_score = evaluate(child_applied_actions, sizes, child_num_actions, new_eval_positions);

			if (new_score > current.score) {
				vll new_remaining_actions = current.remaining_actions;
				new_remaining_actions.erase(new_remaining_actions.begin()+i);
				State child(child_applied_actions, new_remaining_actions, child_num_actions,new_score, new_eval_positions);
				if (history.find(child) == history.end()) {
					agenda.push_back(child);
					push_heap(agenda.begin(), agenda.end());
					history.insert(child);
				} else {
					//unsuccessful.insert(current_action);
					//cerr << "dropping child " << child << " because it's already in the history" << endl;
				}
			} else {
				// cerr << "dropping child " << child << " because score " << child.score << " is worse than the parent's score: " << current.score << endl;
				//unsuccessful.insert(current_action);
			}
		}

		// if (agenda.size() > 4) {
		// 	goto exit;
		// }
	}
exit:
	// cout << "RESULT: " << best_score << endl;
	if (best_score <= 0) 
		best_score = sizes.size();
	//cout << "Search space size: " << search_space << endl;
	cout << "total eval time:" << eval_time/1.0e9 << endl;
	cout << best_score;

	return 0;

}







// void bitvector_test()
// {
// 	Bitvector b1(1);
// 	assert(b1.find_next_live_pos(0) == 0);
// 	assert(b1.find_next_live_pos(1) == -1);
// 	Bitvector b2(2);
// 	assert(b2.find_next_live_pos(0) == 0);
// 	assert(b2.find_next_live_pos(1) == 1);
// 	b2.clear(1);
// 	assert(b2.find_next_live_pos(1) == 0);
// 	b2.clear(0);
// 	assert(b2.find_next_live_pos(1) == -1);

// 	Bitvector b3(65);
// 	for (int i = 0; i < 65; i++)
// 	{
// 		assert(b3.find_next_live_pos(i) == i);
// 		b3.clear(i);
// 	}
// 	assert(b3.find_next_live_pos(0) == -1);

// 	Bitvector b4(65);
// 	for (int i = 0; i < 65; i++)
// 	{
// 		assert(b4.find_next_live_pos(0) == i);
// 		b4.clear(i);
// 	}
// 	assert(b3.find_next_live_pos(0) == -1);

// 	for (int i = 0; i < 100; i++)
// 	{
// 		int size = rand() % 100000 + 10;
// 		// int size = rand() % 5;
// 		int start_pos = rand() % size;
// 		Bitvector b5(size);
// 		for (int j = 0; j < size; j++)
// 		{
// 			int nlp = b5.find_next_live_pos(start_pos);
// 			if (nlp != ((start_pos + j) % size))
// 			{
// 				cerr << "FAIL: nlp: " << dec << nlp << " sp= " << start_pos << " size= " << size << " j=" << j << endl;
// 			}
// 			assert(nlp == ((start_pos + j) % size));
// 			b5.clear((start_pos + j) % size);
// 		}
// 		assert(b5.find_next_live_pos(start_pos) == -1);
// 	}
// }

// size_t the_team_sizes = -1;

// std::ostream &operator<<(std::ostream &s, const Bitvector &b)
// {
// 	for (int i = 0; i < the_team_sizes; i++)
// 	{
// 		s << b.getBit(i);
// 	}
// 	return s;
// }

// namespace std
// {
// 	template <>
// 	struct hash<Bitvector>
// 	{
// 		auto operator()(const Bitvector &v) const -> size_t
// 		{
// 			ll m = 0;
// 			for (ll v : v.longlongs)
// 			{
// 				m += v;
// 			}
// 			return m;
// 		}
// 	};
// }

// class State
// {
// public:
// 	Bitvector bv;
// 	ll score;
// 	ll potential_score;
// 	ll gcd;
// 	ll size;
// 	State(const vll &team_sizes, int add_position) : bv(team_sizes.size()), gcd(team_sizes[add_position]), size(1)
// 	{
// 		bv.clear(add_position);
// 		score = gcd * size;
// 		potential_score = gcd * team_sizes.size();
// 	}
// 	State(const vll &team_sizes, const State &parent, int add_position)
// 		: bv(parent.bv), gcd(compute_gcd(parent.gcd, team_sizes[add_position])), size(parent.size + 1)
// 	{
// 		potential_score = gcd * team_sizes.size();
// 		score = gcd * size;
// 		bv.clear(add_position);
// 	}
// 	bool operator==(const State &o) const
// 	{
// 		return o.bv == bv;
// 	}

// } __attribute__((aligned(sizeof(ll))));


// std::ostream &operator<<(std::ostream &s, const State &st)
// {
// 	s << "[L:" << st.size << "|Sc:" << st.score << "|P:" << st.potential_score << "GCD:" << st.gcd << "|Bits:";
// 	s << st.bv;
// 	s << "]";
// 	return s;
// }

// struct StateCmp
// {
// 	constexpr bool operator()(const State& a, const State&b) const {
// 		return a.score < b.score;
// 	}
// };


// namespace std
// {
// 	template <>
// 	struct hash<State>
// 	{
// 		auto operator()(const State &v) const -> size_t
// 		{
// 			return std::hash<Bitvector>{}(v.bv);
// 		}
// 	};
// }

// int main()
// {

// 	// the_team_sizes=10;
// 	// Bitvector v1(10);
// 	// cerr << v1 << endl;
// 	// v1.clear(1);
// 	// cerr << v1 << endl;
// 	// return 0;


// 	//bitvector_test();
// 	//return 0;

// 	ll N;
// 	cin >> N;
// 	vll sizes;
// 	for (ll i = 1; i <= N; i++)
// 	{
// 		ll size;
// 		cin >> size;
// 		sizes.push_back(size);
// 	}

// 	the_team_sizes = N;

// 	vector<State> agenda_raw;
// 	ll best_score = -1;
// 	for (int i = 0; i < N; i++)
// 	{
// 		agenda_raw.emplace_back(State(sizes, i));
// 	}
// 	priority_queue<State, vector<State>, StateCmp> agenda(agenda_raw.begin(), agenda_raw.end());
// 	unordered_set<State> history;

// 	while (agenda.size() > 0)
// 	{
// 		// cout << "****** AGENDA (" << agenda.size() << ") *****" << endl;
// 		// for (const auto& ai :  agenda) {
// 		// 	cout << ai << endl;
// 		// }
// 		// cout << "********************" << endl;
		
// 		State current = agenda.top();
// 		// cerr << "current: " << current << endl;
// 		agenda.pop();
// 		history.insert(current);
// 		if (current.potential_score > best_score)
// 		{
// 			if (current.score > best_score && current.size > 1)
// 			{
// 				best_score = current.score;
// 				// cerr << "Updated best_score to " << best_score << " from size set=" << current.size << endl;
// 			}
// 			// consider children
// 			ll pos = 0;
// 			ll succs = 0;
// 			ll first_live_pos = -1;
// 			for (;;)
// 			{
// 				//cerr << "p:" << dec << pos << endl;
// 				//cerr << "p:" << dec << pos + 1 << endl;
// 				//int old_pos = pos;
// 				pos = current.bv.find_next_live_pos(pos);
// 				if (pos == first_live_pos) {
// 					break;
// 				}
// 				if (first_live_pos == -1) {
// 					first_live_pos = pos;
// 				}				
// 				//cerr << "Pos (after):" << pos << endl;
// 				if (pos == -1)
// 				{
// 					break;
// 				}				
// 				State new_state(sizes, current, pos);
// 				if (history.find(new_state) == history.end())
// 				{
// 					if (new_state.potential_score > best_score) {
// 						agenda.push(new_state);
// 						succs += 1;
// 					}
// 					if (new_state.score > best_score && new_state.size > 1)
// 					{
// 						best_score = new_state.score;						
// 					}
// 				}
// 				pos += 1;
// 			}
// 			//cerr << "created " << succs << " successor states" << endl;
// 		}
// 		// else
// 		// {
// 		// 	cerr << " .. dropped" << endl;
// 		// }		
// 	}

// 	// cout << "RESULT: " << best_score << endl;
// 	cout << best_score;
// 	return 0;
// }
