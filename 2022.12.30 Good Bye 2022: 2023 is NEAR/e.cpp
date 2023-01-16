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
	int n, k;
	vi a;
	ve<pii> edges;
	
	bool read() {
		if (!(cin >> n >> k)) {
			return 0;
		}
		a.resize(k);
		edges.resize(n - 1);
		forn (i, k) {
			cin >> a[i];
			--a[i];
		}
		forn (i, n - 1) {
			cin >> edges[i].fs >> edges[i].sc;
			--edges[i].fs;
			--edges[i].sc;
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
	ll pow(ll a, ll n) {
		ll ans = 1;
		while (n) {
			if (n & 1) {
				(ans *= a) %= mod;
			}
			(a *= a) %= mod;
			n >>= 1;
		}
		return ans;
	}

	ll inv(ll a) {
		return pow(a, mod - 2);
	}
	
	struct Solution: Data {
		ve<vi> e;
		ve<ll> p;
		ve<ll> cnt_all;
		ve<ll> cnt_ch;

		void dfs(int v, int pr) {
			cnt_all[v] = 1;
			cnt_ch[v] = p[v];
			for (int to : e[v]) {
				if (to == pr) {
					continue;
				}
				dfs(to, v);
				cnt_ch[v] += cnt_ch[to];
				cnt_all[v] += cnt_all[to];
				(ans += 2 * (cnt_ch[to]) * (k - cnt_ch[to])) %= mod;
			}
		}
		
		void solve() {
			cnt_ch = ve<ll>(n, 0);
			cnt_all = ve<ll>(n, 0);
			e.resize(n);
			forn (i, n - 1) {
				e[edges[i].fs].pb(edges[i].sc);
				e[edges[i].sc].pb(edges[i].fs);
			}
			debug(e);
			p = ve<ll>(n, 0);
			forn (i, k) {
				p[a[i]] += 1;
			}
			debug(p);
			ans = 0;
			dfs(0, -1);
			debug(cnt_ch);
			debug(cnt_all);
			debug(ans);
			forn (i, n - 1) {
				int x = edges[i].fs;
				int y = edges[i].sc;
				if (cnt_all[x] < cnt_all[y]) {
					swap(x, y);
				}
				ll cnt_y = cnt_ch[y];
				ll cnt_x = k - cnt_y;
				ll p_x_to_y = p[x] * (1 + mod - p[y]) % mod * inv(2) % mod;
				ll p_y_to_x = p[y] * (1 + mod - p[x]) % mod * inv(2) % mod;
				(ans += 2 * p_x_to_y * (mod + cnt_x - 1 - cnt_y)) %= mod;
				(ans += 2 * p_y_to_x * (mod + cnt_y - 1 - cnt_x)) %= mod;
				ll avg = (p[x] + p[y]) * inv(2) % mod;
				p[x] = avg;
				p[y] = avg;
			}
			(ans *= inv(k)) %= mod;
			(ans *= inv(k - 1)) %= mod;
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
