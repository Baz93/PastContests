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

const int K = 16;
const int M = 16;
const int X = 1 << M;
const int N = X;

const ll mod = 998244353;

struct Input {
	int n, k, m;
	int a[N];
	
	bool read() {
		if (!(cin >> n >> k >> m)) {
			return 0;
		}
		forn (i, n) {
			scanf("%d", &a[i]);
		}
		return 1;
	}

	void init(const Input &input) {
		*this = input;
	}
};

struct Data: Input {
	ll ans[N];

	void write() {
		forn (i, 1 << m) {
			if (i) {
				printf(" ");
			}
			printf("%" PRId64, ans[i]);
		}
		puts("");
	}
};


namespace Main {

	struct Value {
		int cnt;
		ll a[K + 1][X];
	};
	
	struct Solution: Data {
		ll pow_mod(ll x, ll cnt) {
			ll res = 1;
			while (cnt) {
				if (cnt & 1) {
					res = (res * x) % mod;
				}
				x = (x * x) % mod;
				cnt >>= 1;
			}
			return res;
		}

		ll inv_mod(ll x) {
			return pow_mod(x, mod - 2);
		}

		void transform(ll arr[X], bool inv = false) {
			forn (i, m) {
				forn (j, 1 << m) {
					if (!(j & (1 << i))) {
						ll tmp_val = arr[j];
						arr[j] = (arr[j] + arr[j + (1 << i)]) % mod;
						arr[j + (1 << i)] = (tmp_val - arr[j + (1 << i)] + mod) % mod;
					}
				}
			}
			if (inv) {
				ll mul = inv_mod(1 << m);
				forn (j, 1 << m) {
					arr[j] = (arr[j] * mul) % mod;
				}
			}
		}

		void multiply(Value &res, const Value &lhs, const Value &rhs) {
			res.cnt = lhs.cnt + rhs.cnt;
			ll coefx = lhs.cnt * inv_mod(res.cnt) % mod;
			ll coefy = rhs.cnt * inv_mod(res.cnt) % mod;
			ll coef[K + 1][K + 1];
			memset(coef, 0, sizeof coef);
			coef[0][0] = 1;
			memset(res.a, 0, sizeof res.a);
			forn (i, k + 1) {
				forn (j, k - i + 1) {
					if (i) {
						coef[i][j] = (coef[i][j] + coef[i - 1][j] * coefx) % mod;
					}
					if (j) {
						coef[i][j] = (coef[i][j] + coef[i][j - 1] * coefy) % mod;
					}
					forn (t, 1 << m) {
						res.a[i + j][t] = (res.a[i + j][t] + lhs.a[i][t] * rhs.a[j][t] % mod * coef[i][j]) % mod;
					}
				}
			}
		}

		map<vi, int> vec_cnt;

		Value prod;
		Value cur, tmp;
		
		void solve() {
			int xr = 0;
			forn (i, n) {
				xr ^= a[i];
				vi v;
				forn (j, k + 1) {
					v.pb((a[i] - j) ^ a[i]);
				}
				vec_cnt[v]++;
			}
			prod.cnt = 0;
			memset(prod.a, 0, sizeof prod.a);
			prod.a[0][0] = 1;
			transform(prod.a[0]);
			debug(prod.a[0], prod.a[0] + (1 << m));
			for (const auto &p : vec_cnt) {
				debug(p);
				cur.cnt = 1;
				memset(cur.a, 0, sizeof cur.a);
				forn (j, k + 1) {
					cur.a[j][p.fs[j]] = 1;
					transform(cur.a[j]);
				}
				int val = p.sc;
				while (val) {
					if (val & 1) {
						multiply(tmp, prod, cur);
						prod = tmp;
					}
					multiply(tmp, cur, cur);
					cur = tmp;
					val >>= 1;
				}
			}
			transform(prod.a[k], 1);
			forn (i, 1 << m) {
				ans[i] = prod.a[k][i ^ xr];
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
