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

const int N = 2020;

struct Input {
	int n, k;
	
	bool read() {
		return !!(cin >> n >> k);
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
	
	struct Solution: Data {

		bool go(const vi &v, int m) {
			if (m == 0) {
				return sz(v) <= n;
			}
			int len = accumulate(all(v), 0);
			if (len > n) {
				return false;
			}
			vi w;
			forn (i, sz(v)) {
				forn (j, v[sz(v) - 1 - i]) {
					w.pb(i + 1);
				}
			}
			return go(w, m - 1);
		}

		ll calc(vi &v) {
			if (!go(v, k)) {
				return 0;
			}
			ll res = 1;
			v.back()++;
			res = (res + calc(v)) % mod;
			v.back()--;
			v.pb(v.back());
			res = (res + calc(v)) % mod;
			v.pop_back();
			return res;
		}

		map<tu<int, int, int>, ll> mem2;

		ll calc2(int mx0, int len1, int len2) {
			if (len2 > n) {
				return 0;
			}
			auto key = mt(mx0, len1, len2);
			if (mem2.count(key)) {
				return mem2[key];
			}
			ll add = calc2(mx0, len1 + mx0, len2 + len1 + mx0);
			if (add == 0) {
				return mem2[key] = 1;
			}
			return mem2[key] = (add + calc2(mx0 + 1, len1, len2)) % mod;
		}

		map<tu<int, int>, ll> mem1;

		ll calc1(int mx0, int len1) {
			if (len1 > n) {
				return 0;
			}
			auto key = mt(mx0, len1);
			if (mem1.count(key)) {
				return mem1[key];
			}
			ll add = calc1(mx0, len1 + mx0);
			if (add == 0) {
				return mem1[key] = 1;
			}
			return mem1[key] = (add + calc1(mx0 + 1, len1)) % mod;
		}
		
		void solve() {
			debug(mt(n, k));
			if (k > 2) {
				vi v(1, 1);
				ans = calc(v);
			} else if (k == 2) {
				ans = (calc2(1, 0, 0) + mod - 1) % mod;
			} else if (k == 1) {
				ans = (calc1(1, 0) + mod - 1) % mod;
			}
			debug(mem1);
		}

		void precalc() {
			ll ans1[N + 1];
			ll ans2[N + 1];

			forn (i, n + 1) {
				ans2[i] = (calc2(1, 0, n - i) + mod - 1) % mod;
			}
			forn (i, n + 1) {
				ans1[i] = (calc1(1, n - i) + mod - 1) % mod;
			}
			debug(ans2, ans2 + n + 1);
			debug(ans1, ans1 + n + 1);
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

	sol.n = 200;
	sol.precalc();

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
