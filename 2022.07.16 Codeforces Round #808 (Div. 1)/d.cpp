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

struct Input {
	ll mod;
	int n;
	ve<vi> e;
	
	bool read() {
		if (!(cin >> n >> mod)) {
			return 0;
		}
		e = ve<vi>(n);
		forn (i, n - 1) {
			int x, y;
			cin >> x >> y;
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
	ll ans;

	void write() {
		forn (i, 1, n) {
			cout << ans[i] << ' ';
		}
		puts("");
	}
};


namespace Main {

	ll pow(ll a, int n, ll mod) {
		ll ans = 1;
		while (n) {
			if (n & 1) {
				(ans *= a) %= mod;
			}
			(a *= a) %= mod;
			n >>= 1;
		}
		return ans;
	}

	ll inv(ll a, ll mod) {
		return pow(a, mod - 2, mod);
	}
	
	struct Solution: Data {
		ve<ll> f, rf;

		precalc() {
			f.resize(n + 1);
			f[0] = 1;
			forn (i, n) {
				f[i + 1] = f[i] * (i + 1) % mod;
			}
			forn (i, n + 1) {
				rf[i] = inv(f[i]);
			}
		}

		C(int N, int K) {
			return f[N] * rf[K] % mod * rf[N - K] % mod;
		}

		vi cnt;
		ve<ve<ll>> a, b;
		// a - into {root}
		// b - into empty

		void extend(ve<ll> &x, int m) {
			while (sz(x) < m) {
				int k = sz(x);
				x.pb(0);
				sgn = 1;
				ford (i, k - 1) {
					(x[k] += sgn * C(k, i) % mod * x[i]) %= mod;
					sgn = mod - sgn;
				}
			}
		}

		void fold(ve<ll> &x) {
			forn (k, sz(x)) {
				forn (i, k) {
					(x[k] += mod * mod - C(k, i) * x[k]) %= mod;
				}
			}
		}

		void dfs(int v, int pr) {

		}
		
		void solve() {
			precalc();
			cnt = vi(n);
			a = ve<ve<ll>>(n);
			b = ve<ve<ll>>(n);
			dfs(0, -1);
			ans = a[0];
			fold(ans);
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
