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
	int n, m;
	vi a;
	vi b;
	vi x;
	
	bool read() {
		if (!(cin >> n)) {
			return 1;
		}
		a.resize(n);
		b.resize(n);
		forn (i, n) {
			cin >> a[i];
		}
		forn (i, n) {
			cin >> b[i];
		}
		cin >> m;
		x.resize(m);
		forn (i, m) {
			cin >> x[i];
		}
		return 1;
	}

	void init(const Input &input) {
		*this = input;
	}
};

struct Data: Input {
	bool ans;
	
	void write() {
		puts(ans ? "YES" : "NO");
	}
};


namespace Main {
	const int L = 20;
	
	struct Solution: Data {
		map<int, int> cnt;
		ve<pii> pt[L];

		pii get_max(int lb, int rb) {
			int l = 0;
			while ((2 << l) <= rb - lb) {
				++l;
			}
			return max(pt[l][lb], pt[l][rb - (1 << l)]);
		}

		bool rec(int lb, int rb) {
			deepen();
			debug(mt(lb, rb));
			if (lb == rb) {
				return 1;
			}
			int val = get_max(lb, rb).fs;
			debug(val);
			int curr = rb;
			bool need_val = 0;
			while (lb < curr) {
				pii mx = get_max(lb, curr);
				if (mx.fs != val) {
					break;
				}
				int md = mx.sc;
				if (b[md] != a[md]) {
					need_val = 1;
				}
				debug(md);
				if (!rec(md + 1, curr)) {
					return 0;
				}
				curr = md;
			}
			if (need_val) {
				if (cnt[val] == 0) {
					return 0;
				}
				--cnt[val];
			}
			return rec(lb, curr);
		}
		
		void solve() {
			forn (i, m) {
				cnt[x[i]]++;
			}
			debug(a);
			debug(b);
			debug(cnt);
			pt[0].resize(n);
			forn (i, n) {
				pt[0][i] = mp(b[i], i);
			}
			debug(pt[0]);
			forn (i, n) {
				if (a[i] < b[i]) {
					ans = 0;
					return;
				}
			}
			forn (i, L - 1) {
				int sz = n - (2 << i) + 1;
				if (sz <= 0) {
					break;
				}
				pt[i + 1].resize(sz);
				forn (j, sz) {
					pt[i + 1][j] = max(pt[i][j], pt[i][j + (1 << i)]);
				}
				debug(pt[i + 1]);
			}
			ans = rec(0, n);
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
