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

bool ask(ll x) {
	cout << "? " << x << endl;
	string res;
	getline(cin, res);
	return res == "Lucky!";
}

// ll M = 99999999999808;

// bool ask(ll x) {
// 	// debug(x);
// 	// return x <= (1ll << 45);
// 	// return x < (1ll << 46);
// 	return x <= M;
// }

ld f(ld x) {
	// debug(x);
	x = 1 - 1 / (x + 1);
	ld lb = 0.;
	ld rb = 0.5;
	x = lb + (rb - lb) * x;
	// debug(x);
	return x;
}

int solve() {
	ll bad = ll(1e14) + 1;
	ll good = 0;
	ll bal = 1;
	int cnt = 0;
	while (bad - good > 1) {
		// debug(mt(good, bad));
		// debug(bal);
		ll x = good + 1 + ll(0.5 + (bad - good - 2) * f(ld(bal) / bad));
		umn(x, bal);
		umx(x, good);
		++cnt;
		if (ask(x)) {
			good = x;
			bal += x;
		} else {
			bad = x;
			bal -= x;
		}
	}
	cout << "! " << good << endl;
	return cnt;
}

int main() {
	// std::random_device rd;
	// std::mt19937 gen(rd());
	// std::uniform_int_distribution<ll> distrib(0, ll(1e14));

	// for (ll val : {1ll << 45, (1ll << 45) - 1}) {
	// 	M = val;
	// 	int res = solve();
	// 	debug(mt(M, res));
	// 	assert(res <= 105);
	// }
	// // return 0;

	// while (true) {
	// 	M = distrib(gen);
	// 	int res = solve();
	// 	debug(mt(M, res));
	// 	assert(res <= 105);
	// }

	int t;
	cin >> t;
	string s;
	getline(cin, s);
	forn (i, t) {
		solve();
	}
	return 0;
}
