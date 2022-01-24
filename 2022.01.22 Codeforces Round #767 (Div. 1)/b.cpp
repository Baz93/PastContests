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

const int N = 100000;
const int M = N * 3 + 10;
const int C = 26;

struct Input {
	int n;
	string s[N];
	
	bool read() {
		if (!(cin >> n)) {
			return 0;
		}
		getline(cin, s[0]);
		forn (i, n) {
			getline(cin, s[i]);
		}
		return 1;
	}

	void init(const Input &input) {
		*this = input;
	}
};

struct Data: Input {
	bool ans;

	void write() {
		puts(ans ? "YES" : "NO");
	}
};


namespace Main {
	const ull L = (M / 64) + 3;

	int huge_length = 0;

	struct huge {
		ull data[L];

		void reset() {
			memset(data, 0, sizeof data);
		}

		void set(int i) {
			data[i / 64] |= 1ull << i;
		}

		bool test(int i) {
			return data[i / 64] & (1ull << i);
		}

		void spread_left() {
			bool flag = false;
			ford (i, (huge_length + 63) / 64) {
				if (flag) {
					data[i] = ~(0ull);
				} else if (data[i]) {
					ford (j, 64) {
						if (flag) {
							data[i] |= (1ull << j);
						} else if (data[i] & (1ull << j)) {
							flag = true;
						}
					}
				}
			}
		}

		void move_one_left() {
			int x = 0;
			ford (i, (huge_length + 63) / 64) {
				int y = data[i] & 1;
				data[i] >>= 1;
				data[i] |= ull(x) << 63;
				x = y;
			}
		}

		huge& operator|=(const huge &other) {
			forn (i, (huge_length + 63) / 64) {
				data[i] |= other.data[i];
			}
			return *this;
		}

		huge& operator&=(const huge &other) {
			forn (i, (huge_length + 63) / 64) {
				data[i] &= other.data[i];
			}
			return *this;
		}
	};
	
	struct Solution: Data {
		int m;
		string t;
		huge splits;
		huge cur_splits;
		huge letter_mask[C];
		huge global_starts;
		huge starts;
		huge tmp;
		
		void solve() {
			t = "";
			splits.reset();
			splits.set(0);
			forn (i, n) {
				t += s[i];
				splits.set(sz(t));
			}
			debug(t);
			// debug(splits);
			m = sz(t);
			forn (i, C) {
				letter_mask[i].reset();
			}
			forn (i, m) {
				letter_mask[t[i] - 'a'].set(i);
			}
			global_starts.reset();
			starts.reset();
			cur_splits.reset();
			forn (i, m) {
				huge_length = i + 10;
				if (splits.test(i)) {
					starts |= global_starts;
					cur_splits.set(i);
					starts |= cur_splits;
				}
				starts.set(i);
				starts.move_one_left();
				starts &= letter_mask[t[i] - 'a'];
				starts.set(i);
				tmp = starts;
				tmp &= splits;
				tmp.spread_left();
				tmp &= splits;
				starts |= tmp;
				if (splits.test(i + 1)) {
					global_starts |= starts;
				}
			}
			ans = global_starts.test(0);
		}
		
		void clear() {
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
