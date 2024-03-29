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
	int n;
	ll s;
	ve<ll> a;
	
	bool read() {
		if (!(cin >> n >> s)) {
			return 0;
		}
		a.resize(n);
		forn (i, n) {
			cin >> a[i];
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
		ll d_buf[2][2];
		ll v_buf[2][2];
		
		void solve() {
			deepen(0);
			ll *pr_d = d_buf[0];
			ll *cur_d = d_buf[1];
			ll *pr_v = v_buf[0];
			ll *cur_v = v_buf[1];
			cur_v[0] = cur_v[1] = a[0];
			cur_d[0] = cur_d[1] = 0;
			debug(a);
			forn (i, 1, n) {
				swap(pr_d, cur_d);
				swap(pr_v, cur_v);
				debug(pr_v, pr_v + 2);
				debug(pr_d, pr_d + 2);
				if (i == n - 1) {
					cur_v[0] = cur_v[1] = a[i];
				} else {
					if (a[i] < s) {
						cur_v[0] = 0;
						cur_v[1] = a[i];
					} else {
						cur_v[0] = s;
						cur_v[1] = a[i] - s;
					}
				}
				debug(cur_v, cur_v + 2);
				forn (to, 2) {
					cur_d[to] = ll(1e18);
					forn (from, 2) {
						umn(cur_d[to], pr_d[from] + pr_v[from] * cur_v[to]);
					}
					cur_v[to] = a[i] - cur_v[to];
				}
				debug(cur_d, cur_d + 2);
				debug(cur_v, cur_v + 2);
			}
			ans = cur_d[0];
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
