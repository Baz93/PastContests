#include <bits/stdc++.h>
using namespace std;

#ifdef SG
	#include <debug.h>
#else
	template<typename T> struct outputer;
	struct outputable {};
	#define PRINT(...)
	#define OUTPUT(...)
	#define show(...)
	#define debug(...)
	#define deepen(...)
	#define timer(...)
	#define fbegin(...)
	#define fend
	#define pbegin(...)
	#define pend
#endif

#define ARG4(_1,_2,_3,_4,...) _4

#define forn3(i,l,r) for (int i = int(l); i < int(r); ++i)
#define forn2(i,n) forn3 (i, 0, n)
#define forn(...) ARG4(__VA_ARGS__, forn3, forn2) (__VA_ARGS__)

#define ford3(i,l,r) for (int i = int(r) - 1; i >= int(l); --i)
#define ford2(i,n) ford3 (i, 0, n)
#define ford(...) ARG4(__VA_ARGS__, ford3, ford2) (__VA_ARGS__)

#define ve vector
#define pa pair
#define tu tuple
#define mp make_pair
#define mt make_tuple
#define pb emplace_back
#define fs first
#define sc second
#define all(a) (a).begin(), (a).end()
#define sz(a) ((int)(a).size())

typedef long double ld;
typedef int64_t ll;
typedef uint64_t ull;
typedef uint32_t ui;
typedef uint16_t us;
typedef uint8_t uc;
typedef pa<int, int> pii;
typedef pa<int, ll> pil;
typedef pa<ll, int> pli;
typedef pa<ll, ll> pll;
typedef ve<int> vi;

template<typename T> inline auto sqr (T x) -> decltype(x * x) {return x * x;}
template<typename T1, typename T2> inline bool umx (T1& a, T2 b) {if (a < b) {a = b; return 1;} return 0;}
template<typename T1, typename T2> inline bool umn (T1& a, T2 b) {if (b < a) {a = b; return 1;} return 0;}

static const string suit_names = "CDSH";
static const string value_names = "6789TJQKA";

const int S = 4;
const int V = 9;

struct Input {
	int owner[S][V];

	bool read_card(int o) {
		string s;
		if (!(cin >> s)) {
			return 0;
		}
		int suit = int(suit_names.find(s[1]));
		int value = int(value_names.find(s[0]));
		// debug(mt(s, suit, value, o));
		owner[suit][value] = o;
		return 1;
	}
	
	bool read() {
		forn (i, S * V) {
			if (!read_card(i >= S * V / 2)) {
				return 0;
			}
		}
		return 1;
	}

	void init(const Input &input) {
		*this = input;
	}
};

struct Data: Input {
	bool ans;
	
	void write() {
		puts(ans ? "Alice" : "Bob");
	}
};


namespace Main {
	static const int POS = 3;
	
	struct Solution: Data {
		map<pa<int, ve<pii>>, int> d;

		int calc(const ve<pii> &v, int turn) {
			auto key = mp(turn, v);
			if (d.count(key)) {
				return d[key];
			}
			int &res = d[key];
			res = 0;

			bool final = 1;
			forn (i, S) {
				final &= (v[i] == pii{0, V});
			}
			if (final) {
				res = 1;
				return res;
			}

			bool can = 0;
			forn (i, S) {
				if (v[i] == pii{-1, -1}) {
					if (owner[i][POS] == turn) {
						can = 1;
						ve<pii> w = v;
						w[i] = {POS, POS + 1};
						res |= !calc(w, !turn);
					}
				} else {
					if (v[i].fs > 0 && owner[i][v[i].fs - 1] == turn) {
						can = 1;
						ve<pii> w = v;
						w[i] = {v[i].fs - 1, v[i].sc};
						res |= !calc(w, !turn);
					}
					if (v[i].sc < V && owner[i][v[i].sc] == turn) {
						can = 1;
						ve<pii> w = v;
						w[i] = {v[i].fs, v[i].sc + 1};
						res |= !calc(w, !turn);
					}
				}
			}
			if (!can) {
				// forn (i, S) {
				// 	debug(owner[i], owner[i] + V);
				// }
				// debug(v);
				// debug(turn);
				res = !calc(v, !turn);
			}
			return res;
		}
		
		void solve() {
			ans = calc(ve(4, mp(-1, -1)), 0);
		}
		
		void clear() {
			*this = Solution();
		}
	};
}


Main::Solution sol;

int main() {
	cout.setf(ios::showpoint | ios::fixed);
	cout.precision(20);

	#ifdef SG
		freopen((problemname + ".in").c_str(), "r", stdin);
//		freopen((problemname + ".out").c_str(), "w", stdout);
		while (sol.read()) {
			sol.solve();
			sol.write();
			sol.clear();
		}
	#else
		sol.read();
		sol.solve();
		sol.write();
	#endif
	
	/*
	int t;
	cin >> t;
	forn (i, t) {
		sol.read();
		sol.solve();
		sol.write();
		sol.clear();
	}
	*/
	
	return 0;
}
