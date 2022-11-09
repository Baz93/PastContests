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


const ll mod = 1000000007;


struct Input {
	int n, q;
	ve<pa<pii, int>> req;
	
	bool read() {
		if (!(cin >> n >> q)) {
			return 0;
		}
		forn (i, q) {
			int x, y;
			char c;
			cin >> x >> y >> c;
			--x;
			--y;
			int z = 0;
			if (c == 'D') {
				z = 0;
			} else if (c == 'W') {
				z = 1;
			} else if (c == 'L') {
				z = 2;
			}
			req.pb(mp(mp(x, y), z));
		}
		return 1;
	}

	void init(const Input &input) {
		*this = input;
	}
};

struct Data: Input {
	ve<ll> ans;
	
	void write() {
		forn (i, q) {
			cout << ans[i] << endl;
		}
	}
};


namespace Main {
	ve<pii> pr;
	int rnd = 0;

	pii PR(int v) {
		if (pr[v].fs == v) {
			return mp(v, 0);
		}
		pii res = PR(pr[v].fs);
		res.sc += pr[v].sc;
		return pr[v] = res;
	}

	int uni(int x, int y, int z) {
		pii rx = PR(x);
		pii ry = PR(y);
		x = rx.fs;
		y = ry.fs;
		(z += 3 - rx.sc) %= 3;
		(z += ry.sc) %= 3;
		if (x == y) {
			if (z == 0) {
				return 0;
			} else {
				return -1;
			}
		}
		if (rnd ^= 1) {
			swap(x, y);
			z = (3 - z) % 3;
		}
		pr[x] = mp(y, z);
		return 1;
	}
	
	struct Solution: Data {
		ve<ll> pw3;

		void solve() {
			pw3.pb(1);
			forn (i, n) {
				pw3.pb(pw3.back() * 3 % mod);
			}

			pr.resize(n);
			forn (i, n) {
				pr[i] = mp(i, 0);
			}
			debug(pr);

			bool ok = 1;
			ll k = n;
			forn (i, q) {
				int res = uni(req[i].fs.fs, req[i].fs.sc, req[i].sc);
				debug(req[i]);
				debug(res)
				debug(pr);
				ok &= (res != -1);
				k -= res;

				if (!ok) {
					ans.pb(0);
				} else {
					ans.pb(pw3[k]);
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
