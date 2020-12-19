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

const int N = 200000;
const int Q = 200000;
const ll mod = 998244353;

struct Input {
	int n, q;
	string s;
	int p[Q];
	char c[Q];
	
	bool read() {
		if (!(cin >> n >> q)) {
			return 0;
		}
		getline(cin, s);
		getline(cin, s);
		forn (i, q) {
			scanf("%d %c", &p[i], &c[i]);
			--p[i];
		}
		return 1;
	}

	void init(const Input &input) {
		*this = input;
	}
};

struct Data: Input {
	ll ans[Q + 1];

	void write() {
		forn (i, q + 1) {
			printf("%d\n", int(ans[i]));
		}
	}
};


namespace Main {

	ll pw(ll x, ll n) {
		ll res = 1;
		while (n) {
			if (n & 1) {
				res = (res * x) % mod;
			}
			x = (x * x) % mod;
			n >>= 1;
		}
		return res;
	}

	ll inv(ll x) {
		return pw(x, mod - 2);
	}

	const ll r2 = inv(2);
	
	struct Solution: Data {
		ll x = 0, y = 0;
		ll val = 1;
		ll sum_pref = 0;
		ll sum_dif_even = 0;
		ll sum_dif_odd = 0;

		ll sum_pref_even() {
			if (x + y == 0) {
				return 0;
			}
			return
		}

		void flip() {
			swap(x, y);
			sum_pref = (2 * mod + 1 - sum_pref - val) % mod;
		}

		void inc_x() {
			sum_dif_even = 
			sum_pref_even = sum_pref * inv(2) % mod;
			sum_dif = (mod + sum_dif + val + sum_pref - inv(2)) % mod;
			sum_pref = (sum_pref + val * inv(2)) % mod;
			val = val * 2 * (x + y + 1) % mod * inv(x + 1) % mod;
			++x;
		}

		void dec_x() {
			--x;
			val = val * inv(2 * (x + y + 1)) % mod * (x + 1) % mod;
			sum_pref = (mod * mod + sum_pref - val * inv(2)) % mod;
			sum_dif = (2 * mod + sum_dif - val - sum_pref + inv(2)) % mod;
		}

		void inc_y() {
			flip();
			inc_x();
			flip();
		}

		void dec_y() {
			flip();
			dec_y();
			flip();
		}

		ll calc(ll x_, ll y_) {
			debug(mt(x_, y_));
			ll add = 0;
			if (x_ < 0) {
				add = -x_;
				add += add % 2;
				x_ += add;
				y_ -= add;
			}
			if (y_ < 0) {
				add = -y_;
				add += add % 2;
				y_ += add;
				x_ -= add;
			}
			if (y_ < 0) {
				return get(x_ + y_, 0) - y_;
			}
			while (x < x_) {
				inc_x();
			}
			while (x > x_) {
				dec_x();
			}
			while (y < y_) {
				inc_y();
			}
			while (y > y_) {
				dec_y();
			}
			return sum_dif * inv(2) % mod;
		}
		
		void solve() {
			int l[2] = {0, 0};
			int r[2] = {0, 0};

			auto add = [&](int i, int sgn) {
				if (s[i] == 'b') {
					l[i % 2] += sgn;
					r[i % 2] += sgn;
				}
				if (s[i] == '?') {
					r[i % 2] += sgn;
				}
			};

			forn (i, n) {
				add(i, 1);
			}
			forn (i, q + 1) {
				debug(s);
				debug(mt(l[0], r[0], l[1], r[1]));
				ans[i] = calc(r[1] - l[0], r[0] - l[1]);
				if (i < q) {
					add(p[i], -1);
					s[p[i]] = c[i];
					add(p[i], 1);
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
