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


int n;
vi d;

int ask(int v) {
	cout << "? " << v + 1 << endl;
	cout.flush();
	int to;
	cin >> to;
	--to;
	return to;
}

vi c;

void answer() {
	cout << "!";
	forn (i, n) {
		cout << " " << c[i] + 1;
	}
	cout << endl;
	cout.flush();
}

void solve() {
	cin >> n;
	d.resize(n);
	forn (i, n) {
		cin >> d[i];
	}
	vi ord(n);
	iota(all(ord), 0);
	sort(all(ord), [&](int x, int y) {
		return d[x] > d[y];
	});

	int ci = 0;
	c = vi(n, -1);

	for (int v : ord) {
		if (c[v] != -1) {
			continue;
		}

		vi w = {v};
		int col = -1;
		forn (i, d[v]) {
			int to = ask(v);
			if (c[to] != -1) {
				col = c[to];
				break;
			}
			w.pb(to);
		}
		if (col == -1) {
			col = ci++;
		}
		for (int x : w) {
			c[x] = col;
		}
	}

	answer();
}


int main() {
	int t;
	cin >> t;
	forn (i, t) {
		solve();
	}
	
	return 0;
}