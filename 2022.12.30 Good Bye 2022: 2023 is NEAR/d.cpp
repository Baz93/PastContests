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
	vi a, b;
	
	bool read() {
		if (!(cin >> n)) {
			return 0;
		}
		a.resize(n);
		b.resize(n);
		forn (i, n) {
			cin >> a[i];
			--a[i];
		}
		forn (i, n) {
			cin >> b[i];
			--b[i];
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
		vi pr;
		vi cnt;
		vi loop;
		vi used;
		bool rnd = 0;

		int get_pr(int x) {
			if (pr[x] == x) {
				return x;
			}
			return pr[x] = get_pr(pr[x]);
		}


		void uni(int x, int y) {
			bool is_loop = (x == y);
			x = get_pr(x);
			y = get_pr(y);
			loop[x] |= is_loop;
			cnt[x]++;
			if (x == y) {
				return;
			}
			if (rnd ^= 1) {
				swap(x, y);
			}
			pr[x] = y;
			cnt[y] += cnt[x];
			loop[y] |= loop[x];
		}
		
		void solve() {
			pr = vi(n, 0);
			cnt = vi(n, -1);
			loop = vi(n, 0);
			used = vi(n, 0);
			forn (i, n) {
				pr[i] = i;
			}
			forn (i, n) {
				uni(a[i], b[i]);
			}
			ans = 1;
			forn (i, n) {
				int x = get_pr(i);
				if (used[x]) {
					continue;
				}
				used[x] = 1;
				if (cnt[x] != 0) {
					ans = 0;
					return;
				}
				if (loop[x]) {
					(ans *= n) %= mod;
				} else {
					(ans *= 2) %= mod;
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
