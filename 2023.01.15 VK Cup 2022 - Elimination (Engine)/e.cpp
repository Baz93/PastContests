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


const int X = 1000000000;


struct Input {
	int n;
	ve<pa<pii, int>> u, d, b;
	
	bool read() {
		if (!(cin >> n)) {
			return 0;
		}
		forn (i, n) {
			int ub, db, lb, rb;
			cin >> ub >> lb >> db >> rb;
			--ub;
			--lb;
			((db == 1) ? u : ((ub == 1) ? d : b)).pb(mp(mp(lb, rb), i));
		}
		return 1;
	}

	void init(const Input &input) {
		*this = input;
	}
};

struct Data: Input {
	int res;
	ve<tu<int, int, int, int>> ans;

	void write() {
		cout << res << endl;
		forn (i, n) {
			cout << get<0>(ans[i]) + 1 << ' ' << get<2>(ans[i]) + 1 << ' ' << get<1>(ans[i]) << ' ' << get<3>(ans[i]) << endl;
		}	
	}
};


namespace Main {
	
	struct Solution: Data {
		
		void solve() {
			tu<int, int, int, int> none{-1, 0, -1, 0};
			ans.assign(n, none);
			res = 0;
			sort(all(u));
			sort(all(d));
			sort(all(b));
			debug(u);
			debug(d);
			debug(b);
			{
				vi to_u, to_d;
				int umxr = 0;
				int dmxr = 0;
				int ui = 0;
				int di = 0;
				forn (i, sz(b)) {
					while (ui < sz(u) && u[ui].fs.fs <= b[i].fs.fs) {
						umx(umxr, u[ui].fs.sc);
						ui++;
					}
					while (di < sz(d) && d[di].fs.fs <= b[i].fs.fs) {
						umx(dmxr, d[di].fs.sc);
						di++;
					}
					if (umxr >= b[i].fs.sc) {
						to_d.pb(i);
					} else if (dmxr >= b[i].fs.sc) {
						to_u.pb(i);
					}
				}
				int to_u_i = 0;
				int to_d_i = 0;
				int j = 0;
				forn (i, sz(b)) {
					if (to_u_i < sz(to_u) && to_u[to_u_i] == i) {
						u.pb(b[i]);
						to_u_i++;
						continue;
					}
					if (to_d_i < sz(to_d) && to_d[to_d_i] == i) {
						d.pb(b[i]);
						to_d_i++;
						continue;
					}
					b[j++] = b[i];
				}
				b.resize(j);
			}
			sort(all(u));
			sort(all(d));
			sort(all(b));
			debug(u);
			debug(d);
			debug(b);
			{
				int ui = 0;
				int di = 0;
				int mxr = 0;
				forn (i, sz(b) + 1) {
					int lb = mxr;
					int rb = X;

					if (i < sz(b)) {
						int curl = max(b[i].fs.fs, mxr);
						int curr = b[i].fs.sc;
						rb = curl;
						if (curr > curl) {
							ans[b[i].sc] = {0, 2, curl, curr};
							debug(mt(b[i].sc, ans[b[i].sc]));
							res += 2 * (curr - curl);
						}
						umx(mxr, b[i].fs.sc);
					}

					if (lb >= rb) {
						continue;
					}

					int umxr = lb;
					while (ui < sz(u) && u[ui].fs.fs <= rb) {
						int curl = max(u[ui].fs.fs, umxr);
						int curr = min(u[ui].fs.sc, rb);
						if (curr > curl) {
							ans[u[ui].sc] = {0, 1, curl, curr};
							debug(mt(u[ui].sc, ans[u[ui].sc]));
							res += (curr - curl);
						}
						umx(umxr, curr);
						ui++;
					}

					int dmxr = lb;
					while (di < sz(d) && d[di].fs.fs <= rb) {
						int curl = max(d[di].fs.fs, dmxr);
						int curr = min(d[di].fs.sc, rb);
						if (curr > curl) {
							ans[d[di].sc] = {1, 2, curl, curr};
							debug(mt(d[di].sc, ans[d[di].sc]));
							res += (curr - curl);
						}
						umx(dmxr, curr);
						di++;
					}
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
