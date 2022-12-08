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
//typedef long long ll;
typedef int ll;
typedef vector<int> vll;
typedef vector<int> vi;

using fmap = unordered_map<int, int>;

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

inline void update_stat(ll value, ll new_f, fmap& freqs_stat, bool max_mode) {
	auto f = freqs_stat.find(value);
	if (f == freqs_stat.end()
		|| (max_mode && f->second < new_f)
		|| ((!max_mode) && f->second > new_f)) {
		freqs_stat.insert_or_assign(value, new_f);
	} 
}

void primeFactors(ll N, fmap& freqs,
					//fmap& pmin_freqs,
					fmap& pmax_freqs,
					unordered_map<int,vector<int>>& positions_of_factors,
					int pos) {	
	for (int i=0; (i < (int)p.size()) && (p[i]*p[i] <= N); ++i)
	{	
		int c = 0;		
		while (N%p[i] == 0) {			
			N /= p[i];
			c+=1;
		}
		if (c>0) {
			//update_stat(p[i], c, pmin_freqs, false);
			update_stat(p[i], c, pmax_freqs, true);
			freqs.insert(make_pair(p[i],c));
			positions_of_factors[p[i]].push_back(pos);
		}
	}
	if (N != 1) {
		//update_stat(N, 1, pmin_freqs, false);
		update_stat(N, 1, pmax_freqs, true);
		freqs.insert(make_pair(N,1));
		positions_of_factors[N].push_back(pos);
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


ll eval_time = 0;

ll evaluate(ll factors, const vector<ll>& teams, ll num_actions, unordered_map<int,vector<int>>& positions_of_factors, ll current_action) {
	auto start = high_resolution_clock::now();
	ll res=0;
	ll num_teams_covered = 0;
	vector<int>& possible_teams = positions_of_factors[current_action];
	ll num_positions = possible_teams.size();
	for (int i=0; i<num_positions; i++) {
		ll team = teams[possible_teams[i]];
		ll g = team / factors;
		//cout << "gcd(" << factors << "," << team << ")="  << g << endl;
		if ((g * factors == team)) {
			res+=factors;
			num_teams_covered++;
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
	ll score;
	ll num_actions;
	State(const vll& remaining_actions_, ll num_teams)
	: applied_actions(1), remaining_actions(remaining_actions_), score(0), num_actions(0)
	{		
	}
	State(ll applied_actions_, const vll& remaining_actions_, ll num_actions_, ll score_) :
    	applied_actions(applied_actions_), remaining_actions(remaining_actions_), num_actions(num_actions_), score(score_)
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

std::ostream &operator<<(std::ostream &s, const vector<int> &v)
{
	s << "[";
	for (int i=0; i<v.size(); i++) {
		s << v[i];
		if (i<v.size()-1) {
			s << ",";
		}
	}
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
	unordered_map<int,vector<int>> positions_of_factors;
	fmap pmax_freqs;
	for (int i=0;i<N; ++i) {
		pfreqs.emplace_back(fmap{});
		fmap& current = pfreqs.back();
		primeFactors(sizes[i], current, pmax_freqs, positions_of_factors, i);
	}

	vll my_primes;
	for (const auto& f : pmax_freqs) {
		for (int i=0; i<f.second; i++) {
			if (f.first > 1) {
				my_primes.push_back(f.first);
			} else {
				//
			}
		}
	}

	vector<State> agenda;
	ll best_score = -1;
	// initial state
	agenda.emplace_back(State(my_primes, sizes.size()));

	//priority_queue<State, vector<State>, StateCmp> agenda(agenda_raw.begin(), agenda_raw.end());
	unordered_set<State> history;

	//ll search_space = 0;
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

		//search_space++;
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
			ll new_score = evaluate(child_applied_actions, sizes, child_num_actions, positions_of_factors, current_action);

			if (new_score > current.score) {
				vll new_remaining_actions = current.remaining_actions;
				new_remaining_actions.erase(new_remaining_actions.begin()+i);
				State child(child_applied_actions, new_remaining_actions, child_num_actions,new_score);
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
		best_score = N;
	//cout << "Search space size: " << search_space << endl;
	//cout << "total eval time:" << eval_time/1.0e9 << endl;
	cout << best_score;

	return 0;

}
