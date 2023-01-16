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

const ll mod = 998244353;

struct Input {
	int n;
	int raw_p;
	
	bool read() {
		return !!(cin >> n >> raw_p);
	}

	void init(const Input &input) {
		*this = input;
	}
};

struct Data: Input {
	ll ans;

	void write() {
		cout << ans << endl;
	}
};


namespace Main {

	ll pow(ll a, ll n) {
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

	ll inv(ll a) {
		return pow(a, mod - 2);
	}
	
	struct Solution: Data {
		ll p;
		ve<ve<ll>> d;

		ve<ll> f, rf;
		ve<ll> of, rof;
		
		void solve() {
			p = raw_p * inv(10000) % mod;
			f.resize(n + 1);
			rf.resize(n + 1);
			of.resize(n + 1);
			rof.resize(n + 1);
			f[0] = 1;
			of[0] = 1;
			forn (i, n) {
				f[i + 1] = f[i] * (i + 1) % mod;
				of[i + 1] = of[i] * (2 * i + 1) % mod;
			}
			forn (i, n + 1) {
				rf[i] = inv(f[i]);
				rof[i] = inv(of[i]);
			}

			d.resize(n + 1);
			d[0] = ve<ll>(n + 1, 1);

			forn (i, 1, n + 1) {
				d[i] = ve<ll>(n + 1 - i, 0);
				forn (k, 1, i + 1) {
					ll cnt = f[i] * rf[k] % mod * rf[i - k] % mod;
					ll p_each = of[k - 1] * of[i - k] % mod * rof[i] % mod;
					ll p_distr = cnt * p_each % mod;
					forn (depth, sz(d[i])) {
						ll p_up = d[k - 1][depth + 1] * d[i - k][depth] % mod;
						ll p_down = ((depth == 0) ? 0 : d[k - 1][depth - 1] * d[i - k][depth] % mod);
						ll p_good = (p * p_up + (mod + 1 - p) * p_down) % mod;
						(d[i][depth] += p_distr * p_good) %= mod;
					}
				}
			}
			debug(d);
			ans = d[n][0];
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
