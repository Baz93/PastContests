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

const int N = 50;

struct Input {
	int n;
	string s[N];
	
	bool read() {
		if (!(cin >> n)) {
			return 0;
		}
		getline(cin, s[0]);
		forn (i, n) {
			getline(cin, s[i]);
		}
		return 1;
	}

	void init(const Input &input) {
		*this = input;
	}
};

struct Data: Input {
	int ans_k, ans_cnt;
	
	void write(int i) {
		cout << "Case #" << i + 1 << ": ";
		if (ans_k == -1) {
			puts("Impossible");
			return;
		}
		cout << ans_k << ' ' << ans_cnt << endl;
	}
};


namespace Main {
	
	struct Solution: Data {
		int cnto[2][N], cntx[2][N];
		vector<pii> v[2][N];
		
		void solve() {
			memset(cnto, 0, sizeof cnto);
			memset(cntx, 0, sizeof cntx);
			forn (i, n) {
				forn (j, n) {
					if (s[i][j] == 'O') {
						cnto[0][i]++;
						cnto[1][j]++;
					}
					if (s[i][j] == 'X') {
						cntx[0][i]++;
						cntx[1][j]++;
					}
					if (s[i][j] == '.') {
						v[0][i].pb(mp(i, j));
						v[1][j].pb(mp(i, j));
					}
				}
			}
			ans_k = N + 1;
			ve<ve<pii>> q;
			forn (t, 2) {
				forn (i, n) {
					if (cnto[t][i] > 0) {
						continue;
					}
					if (umn(ans_k, n - cntx[t][i])) {
						q.clear();
						ans_cnt = 0;
					}
					if (ans_k == n - cntx[t][i]) {
						q.pb(v[t][i]);
					}
				}
			}
			if (ans_k > N) {
				ans_k = -1;
				return;
			}
			sort(all(q));
			q.erase(unique(all(q)), q.end());
			ans_cnt = sz(q);
			debug(q);
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
	forn (i, t) {
		sol.read();
		sol.solve();
		sol.write(i);
		sol.clear();
	}
	
	return 0;
}
