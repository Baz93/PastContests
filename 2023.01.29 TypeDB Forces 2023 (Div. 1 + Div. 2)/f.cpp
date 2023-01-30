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
	int n, k;
	vi a;
	
	bool read() {
		if (!(cin >> n >> k)) {
			return 0;
		}
		a.resize(n);
		forn (i, n) {
			cin >> a[i];
			--a[i];
		}
		return 1;
	}

	void init(const Input &input) {
		*this = input;
	}
};

struct Data: Input {
	bool can;
	vi ans;

	void write() {
		if (!can) {
			puts("NO");
			return;
		}
		puts("YES");
		forn (i, n) {
			cout << ans[i] + 1 << ' ';
		}
		cout << endl;
	}
};


namespace Main {
	vi transform(const vi &cyc, int k) {
		// debug(cyc);
		// debug(k);
		int n = sz(cyc);
		int m = 1;
		forn (i, k) {
			m = m * 2 % n;
		}
		vi res = vi(n, -1);
		forn (i, n) {
			res[i] = cyc[i * m % n];
		}
		return res;
	}

	vi rev(const vi &cyc, int k) {
		// debug(cyc);
		// debug(k);
		if (k == 0) {
			return cyc;
		}
		int n = sz(cyc);
		assert(n % 2 == 1);
		int phi = 1;
		int m = 2 % n;
		while (m != 1 % n) {
			m = m * 2 % n;
			phi++;
		}
		return transform(cyc, (phi - (k % phi)) % phi);
	}

	vi make(ve<vi> &cyc, int k) {
		// debug(cyc);
		// debug(k);
		forn (i, sz(cyc)) {
			cyc[i] = rev(cyc[i], k);
		}
		debug(cyc);
		int n = sz(cyc[0]);
		vi res;
		forn (i, n) {
			forn (j, sz(cyc)) {
				res.pb(cyc[j][i]);
			}
		}
		return res;
	}
	
	struct Solution: Data {
		
		void solve() {
			debug(k);
			debug(a);
			ve<vi> cyc;
			{
				vi u(n, 0);
				forn (i, n) {
					if (u[i]) {
						continue;
					}
					vi q;
					int v = i;
					while (!u[v]) {
						u[v] = 1;
						q.pb(v);
						v = a[v];
					}
					cyc.pb(q);
				}
			}
			debug(cyc);
			ve<vi> by_len(n + 1);
			forn (i, sz(cyc)) {
				by_len[sz(cyc[i])].pb(i);
			}
			debug(by_len);
			ans = vi(n, -1);
			forn (i, 1, n + 1) {
				if (sz(by_len[i]) == 0) {
					continue;
				}
				if (i % 2 == 0) {
					if (k > 30 || sz(by_len[i]) % (1 << k) != 0) {
						can = 0;
						return;
					}
				}
				ford (t, min(k + 1, 31)) {
					while (sz(by_len[i]) >= (1 << t)) {
						// debug(mt(i, t));
						ve<vi> q;
						forn (j, 1 << t) {
							q.pb(cyc[by_len[i].back()]);
							by_len[i].pop_back();
						}
						debug(q);
						vi res = make(q, k - t);
						debug(res);
						forn (j, sz(res)) {
							ans[res[j]] = res[(j + 1) % sz(res)];
						}
					}
				}
			}
			can = 1;
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
	#endif
	
	int t;
	cin >> t;
	forn (i, t) {
		sol.read();
		sol.solve();
		sol.write();
		sol.clear();
	}
	
	return 0;
}
