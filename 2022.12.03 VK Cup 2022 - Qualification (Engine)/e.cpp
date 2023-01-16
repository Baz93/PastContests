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

ve<string> v = {
	"6C 7C TC AC 8D TD JD AD 6S 7S JS QS KS 6H 7H 9H QH AH",
	"8C 9C JC QC KC 6D 7D 9D QD KD 8S 9S TS AS 8H TH JH KH",
	"",
	"6C 9C JC JD QD KD AD 6S 8S 9S JS AS 7H 8H 9H TH QH KH",
	"7C 8C TC QC KC AC 6D 7D 8D 9D TD 7S TS QS KS 6H JH AH",
	"",
	"7C 9C TC KC AC 6D 8D 9D 6S 8S 9S TS JS QS KS TH JH KH",
	"6C 8C JC QC 7D TD JD QD KD AD 7S AS 6H 7H 8H 9H QH AH",
	"",
	"6C 8C JC AC 7D TD JD AD 6S 7S 9S TS KS 6H 7H 9H TH QH",
	"7C 9C TC QC KC 6D 8D 9D QD KD 8S JS QS AS 8H JH KH AH",
	"",
	"6C TC QC AC 6D TD JD KD AD 8S 9S TS QS 6H 7H 9H QH AH",
	"7C 8C 9C JC KC 7D 8D 9D QD 6S 7S JS KS AS 8H TH JH KH",
	"",
	"6C 7C 9C KC 8D 9D TD JD QD KD 6S TS KS AS 6H TH QH AH",
	"8C TC JC QC AC 6D 7D AD 7S 8S 9S JS QS 7H 8H 9H JH KH",
	"",
	"6C 9C JC QC KC 7D 8D QD KD 6S 8S TS KS 7H 8H TH JH QH",
	"7C 8C TC AC 6D 9D TD JD AD 7S 9S JS QS AS 6H 9H KH AH",
	"",
	"6C 7C 8C TC QC KC AC 6D 7D 9D AD 6S 9S JS QS 6H 9H JH",
	"9C JC 8D TD JD QD KD 7S 8S TS KS AS 7H 8H TH QH KH AH",
	"",
	"6C QC AC 6D 8D 9D QD AD 6S 7S TS AS 9H TH JH QH KH AH",
	"7C 8C 9C TC JC KC 7D TD JD KD 8S 9S JS QS KS 6H 7H 8H",
	"",
	"6C 8C 9C TC 6D 7D QD KD AD 7S TS JS QS AS 9H JH KH AH",
	"7C JC QC KC AC 8D 9D TD JD 6S 8S 9S KS 6H 7H 8H TH QH",
	"",
	"6C TC JC 6D 7D JD QD 6S 7S 9S TS QS KS AS 7H 9H JH QH",
	"7C 8C 9C QC KC AC 8D 9D TD KD AD 8S JS 6H 8H TH KH AH",
	"",
	"6C 7C 8C TC JC QC KC 8D 9D QD KD AD 6S 8S TS QS 8H 9H",
	"9C AC 6D 7D TD JD 7S 9S JS KS AS 6H 7H TH JH QH KH AH",
	"",
	"6C 7C TC JC QC KC AC 6D 9D TD QD 6S 9S JS QS 8H TH JH",
	"8C 9C 7D 8D JD KD AD 7S 8S TS KS AS 6H 7H 9H QH KH AH",
	"",
	"7C JC QC KC AC 6D 7D TD JD QD 6S 7S 9S TS 7H 9H TH JH",
	"6C 8C 9C TC 8D 9D KD AD 8S JS QS KS AS 6H 8H QH KH AH",
	""
};

int main() {
	int k;
	cin >> k;
	forn (i, 3 * k) {
		cout << v[i] << endl;
	}
	return 0;
}
