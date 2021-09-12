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

const ll mod = 1000000007;

struct Input {
	string s;
	
	bool read() {
		int x;
		if (!(cin >> x)) {
			return 0;
		}
		getline(cin, s);
		getline(cin, s);
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

	struct A {
		char first_c = 'F';
		char last_c = 'F';
		ll len = 0;
		ll first_pos = -1;
		ll last_pos = -1;
		ll val_whole = 0;
		ll sum_pref = 0;
		ll sum_suff = 0;
		ll sum_tot = 0;
	};

	A uni(const A &lhs, const A &rhs) {
		A res;
		res.first_c = (lhs.first_c == 'F') ? rhs.first_c : lhs.first_c;
		res.last_c = (rhs.last_c == 'F') ? lhs.last_c : rhs.last_c;
		res.len = (lhs.len + rhs.len) % mod;
		res.first_pos = (lhs.first_c == 'F') ? (lhs.len + rhs.first_pos) % mod : lhs.first_pos;
		res.last_pos = (rhs.last_c == 'F') ? lhs.last_pos : (lhs.len + rhs.last_pos) % mod;
		res.val_whole = (lhs.val_whole + rhs.val_whole) % mod;
		res.sum_pref = (lhs.sum_pref + lhs.val_whole * rhs.len + rhs.sum_pref) % mod;
		res.sum_suff = (lhs.sum_suff + rhs.val_whole * lhs.len + rhs.sum_suff) % mod;
		res.sum_tot = (lhs.sum_tot + lhs.sum_suff * rhs.len + rhs.sum_pref * lhs.len + rhs.sum_tot) % mod;
		if (lhs.last_c != 'F' && rhs.first_c != 'F' && lhs.last_c != rhs.first_c) {
			(res.val_whole += 1) %= mod;
			(res.sum_pref += rhs.len + mod - rhs.first_pos) %= mod;
			(res.sum_suff += lhs.last_pos + 1) %= mod;
			(res.sum_tot += (rhs.len + mod - rhs.first_pos) * (lhs.last_pos + 1)) %= mod;
		}
		return res;
	}
	
	struct Solution: Data {
		
		void solve() {
			A a;
			for (char c : s) {
				if (c == '.') {
					a = uni(a, a);
				} else {
					int pos = (c == 'F') ? -1 : 0;
					a = uni(a, A{c, c, 1, pos, pos, 0, 0, 0, 0});
				}
			}
			ans = a.sum_tot;
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
		// freopen((problemname + ".in").c_str(), "r", stdin);
//		freopen((problemname + ".out").c_str(), "w", stdout);
	#endif
	
	int t;
	cin >> t;
	forn (i, t) {
		sol.read();
		sol.solve();
		printf("Case #%d: ", i + 1);
		sol.write();
		sol.clear();
	}
	
	return 0;
}
