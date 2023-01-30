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
	int n, k, x;

	bool read() {
		return !!(cin >> n >> k >> x);
	}

	void init(const Input &input) {
		*this = input;
	}
};

struct Data: Input {
	bool can;
	ve<vi> ans;

	void write() {
		if (!can) {
			puts("NO");
			return;
		}
		puts("YES");
		forn (i, k) {
			cout << sz(ans[i]);
			forn (j, sz(ans[i])) {
				cout << ' ' << ans[i][j];
			}
			cout << endl;
		}
	}
};


namespace Main {
	
	struct Solution: Data {
		
		void solve() {
			int tx = 0;
			forn (i, 1, n + 1) {
				tx ^= i;
			}
			if (tx != (k % 2) * x) {
				can = 0;
				return;
			}
			vi r;
			forn (i, 1, n + 1) {
				if (i == x) {
					ans.pb(vi{i});
				} else if ((i ^ x) > n) {
					r.pb(i);
				} else if (i < (i ^ x)) {
					ans.pb(vi{i, i ^ x});
				}
			}
			debug(r);
			debug(ans);
			if (sz(ans) < k) {
				can = 0;
				return;
			}
			can = 1;
			while (sz(r)) {
				ans[0].pb(r.back());
				r.pop_back();
			}
			forn (i, k, sz(ans)) {
				while (sz(ans[i])) {
					ans[0].pb(ans[i].back());
					ans[i].pop_back();
				}
			}
			ans.resize(k);
			sort(all(ans[0]));
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
