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


const int K = 3;


struct Input {
	int n, m;
	vi ex, ey;

	bool read() {
		if (!(cin >> n >> m)) {
			return 0;
		}
		ex.resize(m);
		ey.resize(m);
		forn (i, m) {
			cin >> ex[i] >> ey[i];
			--ex[i];
			--ey[i];
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
		forn (i, m) {
			cout << ans[i];
		}
		cout << endl;
	}
};


namespace Main {
	const int V = K + 1;
	const int F = 2 * K;

	uc groups[1 << F][V];
	uc groups_cnt[1 << F];
	uc ok_edges[1 << F];
	uc bit_count[1 << F];
	
	struct Solution: Data {
		vi deg;
		vi is_del;
		int k;
		vi vs;
		vi vs_num;
		ve<vi> e;
		vi ue, uvs;
		ve<pa<pii, vi>> f;

		void dfs(int v_num) {
			if (uvs[v_num]) {
				return;
			}
			uvs[v_num] = 1;
			int v = vs[v_num];
			for (int e_num : e[v]) {
				if (is_del[e_num] || ue[e_num]) {
					continue;
				}
				int w = v;
				vi edges;
				while (true) {
					edges.pb(e_num);
					ue[e_num] = 1;
					w ^= ex[e_num] ^ ey[e_num];
					if (vs_num[w] != -1) {
						break;
					}
					assert(deg[w] == 2);
					for (int q : e[w]) {
						if (is_del[q]) {
							continue;
						}
						e_num ^= q;
					}
				}
				int w_num = vs_num[w];
				f.pb(mp(mp(v_num, w_num), edges));
				dfs(w_num);
			}
		}
		
		void solve() {
			e.resize(n);
			forn (i, m) {
				e[ex[i]].pb(i);
				e[ey[i]].pb(i);
			}
			deg = vi(n, 0);
			forn (i, n) {
				deg[i] = sz(e[i]);
			}
			ans = vi(m, 0);

			is_del = vi(m, 0);
			vi to_remove;
			forn (i, n) {
				if (deg[i] == 1) {
					to_remove.pb(i);
				}
			}
			while (sz(to_remove)) {
				int v = to_remove.back();
				to_remove.pop_back();
				if (!deg[v]) {
					assert(!sz(to_remove));
					break;
				}
				int e_num = -1;
				for (int q : e[v]) {
					if (!is_del[q]) {
						e_num = q;
					}
				}
				int w = ex[e_num] ^ ey[e_num] ^ v;
				is_del[e_num] = 1;
				deg[v]--;
				deg[w]--;
				if (deg[w] == 1) {
					to_remove.pb(w);
				}
			}

			int root = 0;
			forn (i, n) {
				if (deg[i] > deg[root]) {
					root = i;
				}
			}

			vs_num = vi(n, -1);
			forn (i, n) {
				if (deg[i] >= 3 || i == root) {
					vs_num[i] = sz(vs);
					vs.pb(i);
				}
			}
			assert(sz(vs) > 0);
			ue = vi(m, 0);
			uvs = vi(sz(vs), 0);
			debug(vs);
			debug(vs_num);
			debug(e);
			dfs(0);
			debug(f);

			int v_cnt = sz(vs);
			int f_cnt = sz(f);
			assert(v_cnt <= V);
			assert(f_cnt <= F);

			memset(groups, 0, sizeof groups);
			memset(groups_cnt, 0, sizeof groups_cnt);
			memset(ok_edges, 0, sizeof ok_edges);
			memset(bit_count, 0, sizeof bit_count);

			groups_cnt[0] = v_cnt;
			forn (i, v_cnt) {
				groups[0][i] = i;
			}
			forn (bit, f_cnt) {
				forn (msk, 1 << bit) {
					uc *v = groups[msk + (1 << bit)];
					uc &cnt = groups_cnt[msk + (1 << bit)];
					bit_count[msk + (1 << bit)] = bit_count[msk] + 1;
					forn (i, v_cnt) {
						v[i] = groups[msk][i];
					}
					cnt = groups_cnt[msk];
					uc c1 = v[f[bit].fs.fs];
					uc c2 = v[f[bit].fs.sc];
					if (c1 != c2) {
						cnt--;
						forn (i, v_cnt) {
							if (v[i] == c1) {
								v[i] = c2;
							}
						}
					}
				}
			}
			forn (msk, 1 << f_cnt) {
				forn (i, f_cnt) {
					if (msk & (1 << i)) {
						bit_count[msk]++;
					}
					if (
						sz(f[i].sc) >= 2 &&
						groups[msk][f[i].fs.fs] == groups[msk][f[i].fs.sc]
					) {
						ok_edges[msk] |= (1 << i);
					}
				}
			}

			auto best = mt(0, 0, 0);
			int mn = 10 * v_cnt + 100;
			forn (msk1, 1 << f_cnt) {
				for (int msk2 = 0; msk2 <= msk1; msk2 = ((msk2 | msk1) + 1) & ~msk1) {
					int msk3 = ((1 << f_cnt) - 1) ^ msk1 ^ msk2;
					if ((msk3 & ok_edges[msk1] & ok_edges[msk2]) != msk3) {
						continue;
					}
					int cnt = groups_cnt[msk1] + groups_cnt[msk2] - bit_count[msk3];
					if (umn(mn, cnt)) {
						best = mt(msk1, msk2, msk3);
					}
				}
			}

			forn (i, f_cnt) {
				if (get<0>(best) & (1 << i)) {
					debug(mt(0, f[i]));
				} else if (get<1>(best) & (1 << i)) {
					debug(mt(1, f[i]));
					for (int e_num : f[i].sc) {
						ans[e_num] = 1;
					}
				} else if (get<2>(best) & (1 << i)) {
					debug(mt(2, f[i]));
					ans[f[i].sc[0]] = 1;
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
