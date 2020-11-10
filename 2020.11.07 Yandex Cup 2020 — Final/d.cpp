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
	string s;
	
	bool read() {
		return !!getline(cin, s) && sz(s);
	}

	void init(const Input &input) {
		*this = input;
	}
};

struct Data: Input {
	string final_ans;
	
	void write() {
		puts(final_ans.c_str());
	}
};


namespace Main {
	ll inf = ll(1e18);
	
	struct Solution: Data {
		string curs;

		ll rec(int l, ll cur, string &result) {
			if (l == sz(s)) {
				result = curs;
				return cur;
			}

			assert(cur != 0 || s[l] != '0');

			if (cur == 0 || s[l] == '0' || cur == 1 ||
				(l == sz(s) - 1 && s[l] == '1')
			) {
				curs += s[l];
				return rec(l + 1, min<ll>(cur * 10 + (s[l] - '0'), inf), result);
			}

			int prev_sz = sz(curs);
			curs += "**";
			ll ret1 = 1;
			ll pw = rec(l, 0, result);
			while (pw > 0 && ret1 < inf) {
				if (ld(ret1) * ld(cur) > 2 * inf) {
					ret1 = inf;
				} else {
					ret1 = min<ll>(ret1 * cur, inf);
				}
				--pw;
			}
			if (ret1 == inf) {
				return ret1;
			}
			curs.resize(prev_sz);
			curs += s[l];
			string result2;
			ll ret2 = rec(l + 1, min<ll>(cur * 10 + (s[l] - '0'), inf), result2);
			if (ret2 > ret1) {
				result = result2;
				return ret2;
			}
			return ret1;
		}
		
		void solve() {
			rec(0, 0, final_ans);
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
