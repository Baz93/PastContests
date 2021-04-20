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

const int N = 300000;

struct Input {
	int n;
	ll h[N];
	ll b[N];
	
	bool read() {
		if (!(cin >> n)) {
			return 0;
		}
		forn (i, n) {
			scanf("%" SCNd64, &h[i]);
		}
		forn (i, n) {
			scanf("%" SCNd64, &b[i]);
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
		cout << ans << endl;
	}
};


namespace Main {
	
	struct Solution: Data {
		ll d[N];

		pll calc_l(int i, int mn_i) {
			return mp(b[mn_i], d[i] - i * b[mn_i]);
		}

		set<pll> l;

		bool try_del(set<pll>::iterator it) {
			if (it == l.begin()) {
				return 0;
			}
			auto pr = it;
			--pr;
			auto nx = it;
			++nx;
			if (nx == l.end()) {
				return 0;
			}
			auto check = [&]() {
				if (it->fs == pr->fs) {
					return it->sc > pr->sc;
				}
				if (it->fs == nx->fs) {
					return it->sc > nx->sc;
				}
				{
					ld x1 = pr->fs - it->fs;
					ld y1 = pr->sc - it->sc;
					ld x2 = nx->fs - it->fs;
					ld y2 = nx->sc - it->sc;
					ld s = x1 * y2 - x2 * y1;
					if (fabsl(s) > 1e18) {
						return s > 0;
					}
				}
				{
					ll x1 = pr->fs - it->fs;
					ll y1 = pr->sc - it->sc;
					ll x2 = nx->fs - it->fs;
					ll y2 = nx->sc - it->sc;
					ll s = x1 * y2 - x2 * y1;
					return s > 0
				}
			}
			if (check()) {
				return 0;
			}
			l.erase(it);
			return 1;
		}

		void add(const pll &a) {
			auto p = l.insert(a);
			if (!p.second) {
				return;
			}
			auto it = p.first;
			if (try_del(it)) {
				return;
			}
			while (true) {
				if (it == l.begin()) {
					break;
				}
				auto pr = it;
				--pr;
				if (!try_del(pr)) {
					break;
				}
			}
			while (true) {
				auto nx = it;
				++nx;
				if (it == l.end()) {
					break;
				}
				if (!try_del(pr)) {
					break;
				}
			}
		}

		ll calc(ll i) {
			auto it = l.begin();
			ll val = it->fs * i + it->sc;
			while (true) {
				auto nx = it;
				nx++;
				if (nx = l.end()) {
					break;
				}
				ll next_val = nx->fs * i + nx->sc;
				if (next_val <= val) {
					break;
				}
				val = next_val;
				it = nx;
			}
			return val;
		}
		
		void solve() {
			d[0] = 0;
			vi q;
			ve<pll> l;
			forn (i, n) {
				
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
