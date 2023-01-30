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
	ve<tu<int, int, int, int>> adj;
	ve<pii> rs;

	bool read() {
		int q;
		if (scanf("%d%d", &n, &q) != 2) {
			return 0;
		}
		forn (i, n - 1) {
			int x, y, w, c;
			scanf("%d%d%d%d", &x, &y, &w, &c);
			--x;
			--y;
			--c;
			adj.pb(mt(x, y, w, c));
		}
		forn (i, q) {
			int action, v;
			cin >> action >> v;
			--v;
			rs.pb(mp(action, v));
		}
		return 1;
	}

	void init(const Input &input) {
		*this = input;
	}
};

struct Data: Input {
	vi ans;
	
	void write() {
		forn (i, sz(ans)) {
			printf("%d\n", ans[i]);
		}
	}
};


namespace Main {
	
	struct Solution: Data {
		vi w;
		ve<vi> abc;
		ve<vi> e;
		vi p;

		void set_p(int v, int pr) {
			p[v] = pr;
			for (int to : e[v]) {
				if (to == pr) {
					continue;
				}
				set_p(to, v);
			}
		}

		vi enabled;
		vi bad_sons_cnt;
		ve<set<pii, greater<pii>>> vs;
		set<pii, greater<pii>> ts;
		
		void solve() {
			abc.resize(n);
			w.resize(n, 0);
			forn (i, sz(adj)) {
				abc[get<3>(adj[i])].pb(i);
				w[get<3>(adj[i])] += get<2>(adj[i]);
			}
			{
				int vci = 0;
				forn (i, n) {
					if (!sz(abc[i])) {
						continue;
					}
					set<int> all_v;
					forn (j, sz(abc[i])) {
						int x = get<0>(adj[abc[i][j]]);
						int y = get<1>(adj[abc[i][j]]);
						all_v.insert(x);
						all_v.insert(y);
					}
					if (sz(all_v) != sz(abc[i]) + 1) {
						w[i] = 0;
						forn (j, 1, sz(abc[i])) {
							while (sz(abc[vci]) > 0) {
								++vci;
							}
							get<3>(adj[abc[i][j]]) = vci++;
						}
					}
				}
			}
			e.resize(2 * n);
			forn (i, sz(adj)) {
				e[get<0>(adj[i])].pb(n + get<3>(adj[i]));
				e[get<1>(adj[i])].pb(n + get<3>(adj[i]));
				e[n + get<3>(adj[i])].pb(get<0>(adj[i]));
				e[n + get<3>(adj[i])].pb(get<1>(adj[i]));
			}
			forn (i, 2 * n) {
				sort(all(e[i]));
				e[i].erase(unique(all(e[i])), e[i].end());
			}
			p.assign(2 * n, -1);
			set_p(0, -1);
			enabled = vi(n, 1);
			bad_sons_cnt = vi(n, 0);
			vs.resize(n);
			forn (i, n) {
				if (p[n + i] != -1) {
					vs[p[n + i]].insert(mp(w[i], i));
				}
			}
			forn (i, n) {
				vs[i].insert(mp(0, -1));
				ts.insert(mp(vs[i].begin()->fs, i));
			}
			ts.insert(mp(0, -1));
			forn (i, sz(rs)) {
				int action = rs[i].fs;
				int v = rs[i].sc;
				assert(action != enabled[v]);
				if (p[v] != -1 && p[p[v]] != -1) {
					int col = p[v] - n;
					int pr = p[p[v]];
					if (enabled[pr]) {
						ts.erase(mp(vs[pr].begin()->fs, pr));
					}
					if (bad_sons_cnt[col] == 0) {
						vs[pr].erase(mp(w[col], col));
					}
					bad_sons_cnt[col] -= !enabled[v];
					bad_sons_cnt[col] += !action;
					if (bad_sons_cnt[col] == 0) {
						vs[pr].insert(mp(w[col], col));
					}
					if (enabled[pr]) {
						ts.insert(mp(vs[pr].begin()->fs, pr));
					}
				}
				if (enabled[v]) {
					ts.erase(mp(vs[v].begin()->fs, v));
				}
				enabled[v] = action;
				if (enabled[v]) {
					ts.insert(mp(vs[v].begin()->fs, v));
				}
				ans.pb(ts.begin()->fs);
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
