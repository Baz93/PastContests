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
const int K = 50;

struct Input {
	int n, k;
	int a[N];
	vi e[N];
	
	bool read() {
		if (!(cin >> n >> k)) {
			return 0;
		}
		forn (i, n) {
			scanf("%d", &a[i]);
		}
		forn (i, n - 1) {
			int x, y;
			scanf("%d %d", &x, &y);
			--x;
			--y;
			e[x].pb(y);
			e[y].pb(x);
		}
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
	
	struct Solution: Data {
		int d[N][3][K + 1];
		int tmp[3][K + 1];

		void dfs(int v, int pr) {
			d[v][0][0] = 0;
			d[v][2][1] = a[v];
			for (int to : e[v]) {
				if (to == pr) {
					continue;
				}
				dfs(to, v);
				memcpy(tmp, d[v], sizeof tmp);
				forn (i1, 3) {
					forn (j1, N + 1) {
						forn (i2, 3) {
							forn (j2, N + 1) {
								if (d[v][i1][j1] < 0 || d[to][i2][j2] < 0) {
									continue;
								}
								if (j1 + j2 <= k) {
									umx(tmp[i1][j1 + j2], d[v][i1][j1] + d[to][i2][j2]);
								}
								if (j1 + j2 + 1 - (i1 == 1) - (i2 == 1) <= k) {
									umx(
										tmp[
											i1 % 2 + 1
										][
											j1 + j2 + 1 - (i1 == 1) - (i2 == 1)
										],
										d[v][i1][j1] + d[to][i2][j2] + (i1 == 0) * a[v] + (i2 == 0) * a[to] 
									);
								}
							}
						}
					}
				}
				deepen(0);
				forn (i, 3) {
					debug(mt(v, to, i, vi(tmp[i], tmp[i] + k + 1)));
				}
				memcpy(d[v], tmp, sizeof tmp);
			}
			forn (i, 3) {
				debug(mt(v, i, vi(d[v][i], d[v][i] + k + 1)));
			}
		}
		
		void solve() {
			deepen(0);
			debug(a, a + n);
			debug(e, e + n);
			memset(d, -1, sizeof d);
			dfs(0, -1);
			ans = a[0];
			forn (i, 1, 3) {
				forn (j, k + 1) {
					umx(ans, d[0][i][j]);
				}
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
	forn (i, t) {
		sol.read();
		sol.solve();
		sol.write(i);
		sol.clear();
	}
	
	return 0;
}
