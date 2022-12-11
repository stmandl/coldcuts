/*
 * Task:
 * N
 * n1 .. n_N
 *
 * find subset S of the n_i which maximizes lcd(S) * |S| with |S|>=2
 */

// weitere idee: man kann während der evaluierung vielleicht noch
// heruasbekommen, welche factoren keine chance mehr haben.

#include <bits/stdc++.h>
#include <chrono>
using namespace std::chrono;
using namespace std;
// typedef long long ll;
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
	for (ll i = 2; i < _sieve_size; ++i)
		if (bs[i])
		{
			// cross out multiplues of i starting from i*i
			for (ll j = i * i; j < _sieve_size; j += i)
				bs[j] = 0;
			p.push_back(i);
		}
}

bool isPrime(ll N)
{
	if (N < _sieve_size)
		return bs[N];
	abort();
}

inline void update_stat(ll value, ll new_f, fmap &freqs_stat, bool max_mode)
{
	auto f = freqs_stat.find(value);
	if (f == freqs_stat.end() || (max_mode && f->second < new_f) || ((!max_mode) && f->second > new_f))
	{
		freqs_stat.insert_or_assign(value, new_f);
	}
}

void primeFactors(ll N, fmap &freqs,
				  // fmap& pmin_freqs,
				  fmap &pmax_freqs,
				  unordered_map<int, vector<int>> &positions_of_factors,
				  int pos,
				  unordered_map<int, int> &num_positions_of_factors)
{
	for (int i = 0; (i < (int)p.size()) && (p[i] * p[i] <= N); ++i)
	{
		int c = 0;
		while (N % p[i] == 0)
		{
			N /= p[i];
			c += 1;
		}
		if (c > 0)
		{
			// update_stat(p[i], c, pmin_freqs, false);
			update_stat(p[i], c, pmax_freqs, true);
			freqs.insert(make_pair(p[i], c));
			positions_of_factors[p[i]].push_back(pos);
			num_positions_of_factors[p[i]] += 1;
		}
	}
	if (N != 1)
	{
		// update_stat(N, 1, pmin_freqs, false);
		update_stat(N, 1, pmax_freqs, true);
		freqs.insert(make_pair(N, 1));
		positions_of_factors[N].push_back(pos);
		num_positions_of_factors[N] += 1;
	}
}

void print_primefactors(const vll &sizes, const vector<fmap> &freqs)
{
	for (int i = 0; i < sizes.size(); i++)
	{
		cout << sizes[i] << ": ";
		for (auto &f : freqs[i])
		{
			cout << "(" << f.first << "^" << f.second << ")";
		}
		cout << endl;
	}
}

void print_pfreqs(const fmap &freqs, bool end_line = true, std::ostream &s = cout)
{
	for (auto &f : freqs)
	{
		cout << "(" << f.first << ":" << f.second << ")";
	}
	if (end_line)
	{
		cout << endl;
	}
}

void print_vll(std::ostream &s, const vll &v)
{
	for (auto l : v)
	{
		s << l << ",";
	}
}

struct State
{
	friend std::hash<State>;
	ll applied_actions;
	vll remaining_actions;
	ll score;
	bool valid;
	unordered_set<int> dead_actions;
	State(const vll &remaining_actions_, ll num_teams)
		: applied_actions(1), remaining_actions(remaining_actions_), score(0), valid(true), dead_actions()
	{
	}
	State(ll applied_actions_, const vll &remaining_actions_, ll score_, const unordered_set<int>& dead_actions_) : applied_actions(applied_actions_), remaining_actions(remaining_actions_), score(score_), valid(true), dead_actions(dead_actions_)
	{
	}
	bool operator==(const State &o) const
	{
		// assert (this->valid && o.valid);
		return applied_actions == o.applied_actions && remaining_actions == o.remaining_actions;
	}
	friend bool operator<(const State &a, const State &b)
	{
		// assert (a.valid && b.valid);
		return a.score < b.score;
	}
	State(const State &) = delete;
	State(State &&other)
		: applied_actions(other.applied_actions),
		  remaining_actions(std::move(other.remaining_actions)),
		  score(other.score)
	{
		other.remaining_actions = std::vector<ll>();
	}
	State &operator=(State &&other)
	{
		applied_actions = other.applied_actions;
		remaining_actions = std::move(other.remaining_actions);
		score = other.score;
		other.remaining_actions = std::vector<ll>();
		return *this;
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
	constexpr bool operator()(const State &a, const State &b) const
	{
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
	for (int i = 0; i < v.size(); i++)
	{
		s << v[i];
		if (i < v.size() - 1)
		{
			s << ",";
		}
	}
	s << "]";
	return s;
}

struct Solver
{

	// ll eval_time = 0;

	ll evaluate(ll factors, const vector<ll> &teams, unordered_map<int, vector<int>> &positions_of_factors, ll current_action)
	{
		// auto start = high_resolution_clock::now();
		ll res = 0;
		ll num_teams_covered = 0;
		vector<int> &possible_teams = positions_of_factors[current_action];
		ll num_positions = possible_teams.size();
		for (int i = 0; i < num_positions; i++)
		{
			ll team = teams[possible_teams[i]];
			// ll g = team / factors;
			if ((team % factors) == 0)
			{
				res += factors;
				num_teams_covered++;
			}
		}
		if (num_teams_covered < 2)
		{
			res = 0;
		}
		return res;
	};
	vll sizes;
	vll my_primes;
	vector<fmap> pfreqs;
	unordered_map<int, vector<int>> positions_of_factors;
	unordered_map<int, int> num_positions_of_factors;
	fmap pmax_freqs;


	Solver(const vll &sizes_, bool with_pruning)
		: sizes(sizes_)
	{
		// factorize

		for (int i = 0; i < sizes.size(); ++i)
		{
			pfreqs.emplace_back(fmap{});
			fmap &current = pfreqs.back();
			primeFactors(sizes[i], current, pmax_freqs, positions_of_factors, i, num_positions_of_factors);
		}

		for (const auto &f : pmax_freqs)
		{
			if (f.second > 1)
			{
				for (int i = 0; i < f.second; i++)
				{
					my_primes.push_back(f.first);
				}
			}
		}

	}
	int solve()
	{
		vector<State> agenda;
		ll best_score = -1;
		// initial state
		agenda.emplace_back(State(my_primes, sizes.size()));
		unordered_set<int> history;
		// unordered_set<int> dead_actions;
		while (agenda.size() > 0)
		{
			// cout << "****** AGENDA (" << agenda.size() << ") *****" << endl;
			// for (const auto& ai :  agenda) {
			// 	cout << ai << endl;
			// }
			// cout << "********************" << endl;
			std::pop_heap(agenda.begin(), agenda.end());
			State current = move(agenda.back());
			agenda.pop_back();

			size_t current_remaining_size = current.remaining_actions.size();
			for (int i = 0; i < current_remaining_size; i++)
			{

				ll current_action = current.remaining_actions[i];
				if (current.dead_actions.find(current_action) != current.dead_actions.end()) {
					continue;
				}
				
				ll child_applied_actions = current.applied_actions * current_action;
				if (history.find(child_applied_actions) != history.end())
				{
					continue;
				}
				
				ll new_score = evaluate(child_applied_actions, sizes, positions_of_factors, current_action);

				if (new_score > current.score)
				{
					unordered_set<int> new_dead_actions(current.dead_actions.begin(), current.dead_actions.end());
					vll new_remaining_actions = current.remaining_actions;
					new_remaining_actions.erase(new_remaining_actions.begin() + i);
					agenda.emplace_back(State(child_applied_actions, new_remaining_actions, new_score,new_dead_actions));
					push_heap(agenda.begin(), agenda.end());
					history.insert(child_applied_actions);

					if (new_score > best_score)
					{
						best_score = new_score;
					}
				} else {
					current.dead_actions.insert(current_action);
				}
			}
		}
		if (best_score <= 0)
			best_score = sizes.size();
		return best_score;
	}
};

int main()
{
	ll max_prime = ll(sqrt(2'000'000)) + 1;
	// cout << "BP=" << max_prime << endl;
	sieve(max_prime);

	// read input
	ll N;
	cin >> N;
	int max_input = 0;
	vll sizes;
	for (ll i = 1; i <= N; i++)
	{
		ll size;
		cin >> size;
		sizes.push_back(size);
		if (size > max_input)
		{
			max_input = size;
		}
	}

	Solver solver(sizes, true);
	cout << solver.solve();

	return 0;
}
