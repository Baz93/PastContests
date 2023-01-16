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

	void write() {
		forn (p, 2) {
			forn (i, S) {
				forn (j, V) {
					if (owner[i][j] == p) {
						cout << value_names[j] << suit_names[i] << ' ';
					}
				}
			}
			cout << endl;
		}
		cout << endl;
	}

	void init(const Input &input) {
		*this = input;
	}
};


namespace Main {
	static const int POS = 3;

	static const int L = POS + 1;
	static const int R = V - POS;
	static const int K = L * R + 1;
	static const int M = K * K * K * K * 2;
	static const int inf = S * V + 1;
	
	struct Solution: Input {
		char prs[S][V + 1][2];

		char d[M];

		char calc(const ve<pii> &v, int turn) {
			int key = 0;
			forn (i, S) {
				key *= K;
				if (v[i] == pii{-1, -1}) {
					key += L * R;
				} else {
					key += R * v[i].fs + (V - v[i].sc);
				}
			}
			key *= 2;
			key += turn;

			if (d[key] != inf) {
				return d[key];
			}
			char &res = d[key];
			res = -inf;

			char cnt[2] = {0, 0};
			forn (i, S) {
				forn (p, 2) {
					cnt[p] += prs[i][V][p];
					if (v[i] != pii{-1, -1}) {
						cnt[p] -= prs[i][v[i].sc][p] - prs[i][v[i].fs][p];
					}
				}
			}
			if (cnt[!turn] == 0) {
				res = -cnt[turn];
				return res;
			}

			bool can = 0;
			forn (i, S) {
				if (v[i] == pii{-1, -1}) {
					if (owner[i][POS] == turn) {
						can = 1;
						ve<pii> w = v;
						w[i] = {POS, POS + 1};
						umx(res, -calc(w, !turn));
					}
				} else {
					if (v[i].fs > 0 && owner[i][v[i].fs - 1] == turn) {
						can = 1;
						ve<pii> w = v;
						w[i] = {v[i].fs - 1, v[i].sc};
						umx(res, -calc(w, !turn));
					}
					if (v[i].sc < V && owner[i][v[i].sc] == turn) {
						can = 1;
						ve<pii> w = v;
						w[i] = {v[i].fs, v[i].sc + 1};
						umx(res, -calc(w, !turn));
					}
				}
			}
			if (!can) {
				res = -calc(v, !turn);
			}
			return res;
		}
		
		int solve() {
			// timer();
			memset(prs, 0, sizeof prs);
			forn (i, S) {
				forn (j, V) {
					forn (p, 2) {
						prs[i][j + 1][p] = prs[i][j][p] + (owner[i][j] == p);
					}
				}
			}
			memset(d, inf, sizeof d);
			int score[2];
			forn (p, 2) {
				score[p] = calc(ve(4, mp(-1, -1)), p);
			}
			return abs(score[0] + score[1]);
		}
		
		void clear() {
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
			int ans = sol.solve();
			debug(ans);
			sol.write();
			sol.clear();
		}
		cout << "=======================" << endl << endl;
	#else
		sol.read();
		sol.solve();
		sol.write();
	#endif
	
	set<int> found;

	while (1) {
		vi v(S * V);
		forn (i, S * V) {
			v[i] = i % 2;
		}
		random_shuffle(all(v));
		forn (i, S) {
			forn (j, V) {
				sol.owner[i][j] = v[i * V + j];
			}
		}
		int ans = sol.solve();
		if (!found.count(ans)) {
			found.insert(ans);
			debug(ans);
			debug(found.size());
			sol.write();
		}
		sol.clear();
	}
	
	return 0;
}
