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

const ld pi = acosl(-1);

template<typename T> inline auto sqr (T x) -> decltype(x * x) {return x * x;}
template<typename T1, typename T2> inline bool umx (T1& a, T2 b) {if (a < b) {a = b; return 1;} return 0;}
template<typename T1, typename T2> inline bool umn (T1& a, T2 b) {if (b < a) {a = b; return 1;} return 0;}

const int N = 500000;

struct Input {
	string s;
	
	bool read() {
		return !!getline(cin, s) && sz(s);
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
		static const int L = 20;
		static const int M = 1 << L;
		
		void butterfly (ld *x, ld *y, int n) {
			for (int i = 1, j = 0; i < n; ++i) {
				int k = n >> 1;
				while (j >= k) {
					j -= k;
					k >>= 1;
				}
				j += k;
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
				for (int k = 0; k < n; k += m << 1) {
					ld wx = 1, wy = 0;
					for (int j = k; j < k + m; j++) {
						ld vx = x[j + m] * wx - y[j + m] * wy;
						ld vy = x[j + m] * wy + y[j + m] * wx;					
						x[j + m] = x[j] - vx;
						y[j + m] = y[j] - vy;
						x[j] += vx;
						y[j] += vy;
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
		
		ld ax[M], ay[M];

		ld _a[M], _c[M];
		int _b[M];

		void rec(int l, int r) {
			if (r - l == 1) {
				return;
			}
			int md = (r + l) / 2;
			int ss = (r - l) / 2;
			rec(l, md);
			rec(md, r);
			memcpy(ax, _a + l, ss * sizeof(ld));
			memcpy(ay, _c + md, ss * sizeof(ld));
			memset(ax + ss, 0, ss * sizeof(ld));
			memset(ay + ss, 0, ss * sizeof(ld));
			debug(mt(l, r));
			debug(ax, ax + 2 * ss);
			debug(ay, ay + 2 * ss);
			
			fft(ax, ay, 2 * ss);
			forn (i, 2 * ss) {
				ld x_ = ax[i];
				ax[i] = ax[i] * ax[i] - ay[i] * ay[i];
				ay[i] = 2 * x_ * ay[i];
			}
			fft(ax, ay, 2 * ss);
			inv(ax, ay, 2 * ss);
			
			debug(ay, ay + 2 * ss);
			debug(_b + l, _b + r);

			forn (i, 2 * ss) {
				if ((l + md + i) % 2) {
					continue;
				}
				ll val = ll(ay[i] / 2 + 0.5);
				debug(mt(i, _b[(l + md + i) / 2], val));
				ans += _b[(l + md + i) / 2] * val;
			}
		}
		
		void solve () {
			debug();	
			debug(s);
			int ss = 1;
			while (ss < sz(s)) {
				ss *= 2;
			}
			memset(_a, 0, sizeof _a);
			memset(_b, 0, sizeof _b);
			forn (i, sz(s)) {
				if (s[i] == 'a') {
					_a[i] = 1;
				}
				if (s[i] == 'A') {
					_a[i] = 2;
				}
				if (s[i] == 'b') {
					_b[i] = 1;
				}
				if (s[i] == 'B') {
					_b[i] = 2;
				}
				if (s[i] == 'c') {
					_c[i] = 1;
				}
				if (s[i] == 'C') {
					_c[i] = 2;
				}
			}

			ans = 0;
			rec(0, ss);
		}
		
		void clear () {
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
