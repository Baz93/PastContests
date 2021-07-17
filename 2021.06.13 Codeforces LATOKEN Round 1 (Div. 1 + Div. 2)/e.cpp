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

const int N = 500;

ve<vi> v;

vi inverse(vi w, int n) {
	sort(all(w));
	vi res = 0;
	int j = 0;
	forn (i, n) {
		if (j < sz(w) && w[j] == i) {
			++j;
		} else {
			res.pb(i);
		}
	}
	return res;
}

bool solve(int n, int k) {
	if (n < k) {
		return 0;
	}
	if (k % 2 == 0 && n % 2 == 1) {
		return 0;
	}

	bool inv = 0;
	int n0 = n;
	if (n > k && n < 2 * k) {
		inv = 1;
		k = n - k;
	}

	int bal = 0;

	while (
		n > 4 * k ||
		(n <= 4 * k && n > 3 * k && n % 2 == 1)
	) {
		vi w;
		forn (i, k) {
			w.pb(n - 1 - i);
		}
		v.pb(w);
		n -= k;
		bal ^= inv;
	}
	debug(n);
	if (n == 0) {
		return 1;
	}
	int choose = (n < 3 * k && n % 2 == k % 2) ? 3 : 4;
	debug(choose);
	assert(n > k && n <= choose * k);
	if (choose == 3) {
		assert(n % 2 == k % 2);
		int x = (3 * k - n) / 2;
		forn (t, 3) {
			vi w;
			forn (i, k - x) {
				w.pb(t * (k - x) + i);
			}
			forn (i, x) {
				w.pb(n - 1 - i);
			}
			v.pb(w);
		}
	} else {
		assert(n % 2 == 0);
		int x = n / 2 - k;
		int a[4], b[4];
		forn (i, 4) {
			a[i] = (2 * k - n / 2 + i) / 4;
			b[i] = a[i] + x;
		}
		debug(a, a + 4);
		debug(b, b + 4);
		forn (i, 4) {
			assert(a[i] >= 0);
			assert(b[i] >= 0);
		}
		forn (t, 4) {
			vi w;
			int i = 0;
			forn (l, 4) {
				if (l != t) {
					forn (cnt, a[l]) {
						w.pb(i++);
					}
				} else {
					i += a[l];
				}
			}
			forn (l, 4) {
				if (l == t) {
					forn (cnt, b[l]) {
						w.pb(i++);
					}
				} else {
					i += b[l];
				}
			}
			v.pb(w);
		}
	}

	if (inv) {
		for (auto &w : v) {
			w = inverse(w, n0);
		}
	}

	return 1;
}

int n, k;

int cnt[N];

bool check() {
	memset(cnt, 0, sizeof cnt);
	forn (i, sz(v)) {
		if (sz(v[i]) != k) {
			return 0;
		}
		for (int x : v[i]) {
			cnt[x]++;
		}
	}
	debug(cnt, cnt + n);
	forn (i, n) {
		if (cnt[i] % 2 == 0) {
			return 0;
		}
	}
	return 1;
}

int main() {
	cin >> n >> k;
	bool res = solve(n, k);
	if (!res) {
		puts("-1");
		fflush(stdout);
		return 0;
	}
	debug(v);
	assert(check());

	ll ans = 0;
	forn (i, sz(v)) {
		cout << "?";
		forn (j, sz(v[i])) {
			cout << ' ' << v[i][j] + 1;
		}
		cout << endl;
		cout.flush();
		ll val;
		cin >> val;
		ans ^= val;
	}
	cout << "! " << ans << endl;
	return 0;
}
