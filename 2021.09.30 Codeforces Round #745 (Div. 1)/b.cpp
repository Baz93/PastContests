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

const int N = 100;

struct Input {
	int n, m, k, mod;
	
	bool read() {
		return !!(cin >> n >> m >> k >> mod);
	}

	void init(const Input &input) {
		*this = input;
	}
};

struct Data: Input {
	int ans;
	
	void write() {
		cout << ans << endl;
	}
};


namespace Main {
	
	int pw (int a, int n, int mod) {
		int res = 1;
		while (n) {
			if (n & 1) {
				res = res * 1ll * a % mod;
			}
			a = a * 1ll * a % mod;
			n >>= 1;
		}
		return res;
	}

	int inv (int a, int mod) {
		return p
	}

	const ld pi = acosl(-1);
	const int M = 1 << 19;
	ld ax[M], ay[M], bx[M], by[M];
	ld cx[M], cy[M], dx[M], dy[M];
	
	void butterfly (ld *x, ld *y, int n) {
		for (int i = 1, j = 0; i < n; ++i) {
			for (int k = n >> 1; (j ^= k) < k; k >>= 1) {}
			if (i < j) {
				swap(x[i], x[j]);
				swap(y[i], y[j]);
			}
		}
	}
	
	void fft (ld *x, ld *y, int n) {
		butterfly(x, y, n);
		for (int m = 1; m < n; m <<= 1) {
			ld rx = cosl(pi / m), ry = sinl(pi / m);
			for (int i = 0; i < n; i += m << 1) {
				ld wx = 1, wy = 0;
				for (int j = i; j < i + m; ++j) {
					ld ux = x[j], uy = y[j];
					ld vx = x[j + m] * wx - y[j + m] * wy;
					ld vy = x[j + m] * wy + y[j + m] * wx;
					x[j] = ux + vx;
					y[j] = uy + vy;
					x[j + m] = ux - vx;
					y[j + m] = uy - vy;
					ld x_ = wx;
					wx = x_ * rx - wy * ry;
					wy = x_ * ry + wy * rx;
				}
			}
		}
	}
	
	void inv (ld *x, ld *y, int n) {
		forn (i, n) {
			x[i] /= n;
			y[i] /= n;
		}
		reverse(x + 1, x + n);
		reverse(y + 1, y + n);
	}
	
	const int D = 30000;
	
	vi mult (vi a, vi b, int mod) {
		int k = sz(a) + sz(b) - 1;
		int n = 1;
		while (n < k) {
			n *= 2;
		}
		a.resize(n);
		b.resize(n);
		forn (i, n) {
			ax[i] = a[i] % D;
			ay[i] = a[i] / D;
			bx[i] = b[i] % D;
			by[i] = b[i] / D;
		}
		fft(ax, ay, n);
		fft(bx, by, n);
		forn (i, n) {
			cx[i] = ax[i] * bx[i] - ay[i] * by[i];
			cy[i] = ax[i] * by[i] + ay[i] * bx[i];
		}
		reverse(ax + 1, ax + n);
		reverse(ay + 1, ay + n);
		forn (i, n) {
			dx[i] = ax[i] * bx[i] + ay[i] * by[i];
			dy[i] = ax[i] * by[i] - ay[i] * bx[i];
		}
		fft(cx, cy, n);
		inv(cx, cy, n);
		fft(dx, dy, n);
		inv(dx, dy, n);
		vi res(k);
		forn (i, sz(res)) {
			ll p00 = ll((dx[i] + cx[i]) / 2 + 0.5) % mod;
			ll p11 = ll((dx[i] - cx[i]) / 2 + 0.5) % mod;
			ll p01 = ll((cy[i] + dy[i]) / 2 + 0.5) % mod;
			ll p10 = ll((cy[i] - dy[i]) / 2 + 0.5) % mod;
			res[i] = (p00 + p01 * D + p10 * D + p11 * D * D) % mod;
		}
		return res;
	}
	
	ve<vi> mult (const ve<vi> &a, const ve<vi> &b, int mod) {
		debug(a);
		debug(b);
		int n = sz(a) + sz(b) - 1;
		int m = sz(a[0]) + sz(b[0]) - 1;
		vi aa(n * m, 0), bb(n * m, 0);
		forn (i, sz(a)) {
			forn (j, sz(a[0])) {
				aa[i * m + j] = a[i][j];
			}
		}
		forn (i, sz(b)) {
			forn (j, sz(b[0])) {
				bb[i * m + j] = b[i][j];
			}
		}
		vi cc = mult(aa, bb, mod);
		ve<vi> c(n, vi(m, 0));
		forn (i, n) {
			forn (j, m) {
				c[i][j] = cc[i * m + j];
			}
		}
		debug(c);
		return c;
	}
	
	struct Solution: Data {
		int d[N + 1][N + 1][N + 1];
		int f[N + 1], rf[N + 1];
		
		void solve() {
			memset(d, 0, sizeof d);
			d[0][1][0] = 1;
			forn (i, n + 1) {
				d[i][1][bool(i)] = 1;
			}

			forn (t, 1, m) {
				ve<vi> a(n + 1, vi(k + 1));
				forn (i, n + 1) {
					forn (j, k + 1) {
						a[i][j] = d[i][t][j];
					}
				}
				ve<vi> res = mult(a, a, mod);
				forn (i, n + 1) {
					forn (j, k + 1) {
						if (i == 0) {
							d[i][t + 1][j] = (j == 0);
						} else {
							d[i][t + 1][j] = res[i - 1][j];
						}
					}
				}
			}
			forn (t, 1, m + 1) {
				debug(t);
				forn (i, n + 1) {
					debug(d[i][t], d[i][t] + k + 1);
				}
			}
			ans = d[n][m][k];
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
