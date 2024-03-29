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

int ask(int k, const vi &v) {
	assert(v[k] == 0);
	if (accumulate(all(v), 0) == 0) {
		return 0;
	}
	cout << "? " << k + 1 << ' ';
	forn (i, n) {
		cout << v[i];
	}
	cout << endl;
	cout.flush();
	int res;
	cin >> res;
	return res;
}

void answer(const vi &v) {
	cout << "! ";
	forn (i, n) {
		cout << v[i];
	}
	cout << endl;
	cout.flush();
}

int main() {
	cout.setf(ios::showpoint | ios::fixed);
	cout.precision(20);

	cin >> n;

	vi ord;
	{
		vi u(n, 0);
		forn (i, n) {
			int cnt = ask(i, u);
			u[i] = 1;
			ord.insert(ord.begin() + cnt, i);
		}
	}
	debug(ord);
	{
		vi u(n, 0);
		int j = n;
		ford (i, n) {
			debug(i);
			int v = ord[i];
			if (i == n - 1 || ask(v, u) > 0) {
				while (j > i) {
					--j;
					u[ord[j]] = 1;
				}
			}
			debug(j);
			debug(u);
		}
		answer(u);
	}

	return 0;
}
