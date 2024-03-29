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

void read_empty_line() {
	string s;
	getline(cin, s);
}

const int M = 300;

struct Input {
	string s;
	int m;
	char from[M], to[M];
	
	bool read() {
		if (!getline(cin, s)) {
			return 0;
		}
		cin >> m;
		forn (i, m) {
			cin >> from[i] >> to[i];
		}
		read_empty_line();
		return 1;
	}

	void init(const Input &input) {
		*this = input;
	}
};

struct Data: Input {
	int ans;
	
	void write(int i) {
		cout << "Case #" << i + 1 << ": " << ans << endl;
	}
};


namespace Main {
	const int X = 10000;
	
	struct Solution: Data {
		int cnt[26];

		int d[26][26];

		void solve() {
			forn (i, 26) {
				forn (j, 26) {
					d[i][j] = X;
				}
			}
			forn (i, 26) {
				d[i][i] = 0;
			}
			forn (i, m) {
				d[from[i] - 'A'][to[i] - 'A'] = 1;
			}

			forn (i, 26) {
				forn (j, 26) {
					forn (k, 26) {
						umn(d[j][k], d[j][i] + d[i][k]);
					}
				}
			}

			// forn (i, 26) {
			// 	debug(d[i], d[i] + 26);
			// }

			debug(s);
			memset(cnt, 0, sizeof cnt);
			for (char c : s) {
				cnt[c - 'A']++;
			}
			debug(cnt, cnt + 26);
			ans = X;
			forn (i, 26) {
				int cur = 0;
				forn (j, 26) {
					cur += cnt[j] * d[j][i];
				}
				umn(ans, cur);
				// debug(mt(i, cur));
			}
			if (ans == X) {
				ans = -1;
			}
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
		// freopen((problemname + ".in").c_str(), "r", stdin);
//		freopen((problemname + ".out").c_str(), "w", stdout);
	#endif
	
	int t;
	cin >> t;
	read_empty_line();
	forn (i, t) {
		sol.read();
		sol.solve();
		sol.write(i);
		sol.clear();
	}
	
	return 0;
}
