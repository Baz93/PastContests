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

const int N = 20000;

int n;
vi e[N];

int root = -1;
int parent[N];
int l[N], cnt[N];

void remove_edge_one_way(int x, int y) {
	for (int &to: e[x]) {
		if (to == y) {
			swap(to, e[x].back());
			break;
		}
	}
	assert(e[x].back() == y);
	e[x].pop_back();
}

void remove_edge(int x, int y) {
	root = -1;
	remove_edge_one_way(x, y);
	remove_edge_one_way(y, x);
}

map<pii, int> mem;

int query(int x, int y) {
	if (x == y) {
		return 0;
	}
	if (mem.count(mp(x, y))) {
		return mem[mp(x, y)];
	}
	cout << "? " << x + 1 << ' ' << y + 1 << endl;
	int res;
	cin >> res;
	mem[mp(x, y)] = mem[mp(y, x)] = res;
	return res;
}

int advantage(int v) {
	return l[v] - query(root, v);
}

void dfs_prepare(int v, int pr, int curl) {
	parent[v] = pr;
	l[v] = curl;
	cnt[v] = 1;
	for (int to : e[v]) {
		if (to == pr) {
			continue;
		}
		dfs_prepare(to, v, curl + 1);
		cnt[v] += cnt[to];
	}
}

void prepare(int v) {
	if (root == v) {
		return;
	}
	root = v;
	dfs_prepare(v, -1, 0);
}

void optimize(int &v) {
	int mx = advantage(v);
	while (true) {
		bool done = false;
		for (int to : e[v]) {
			int cur = advantage(to);
			if (umx(mx, cur) || (mx == cur && to == parent[v])) {
				v = to;
				done = true;
				break;
			}
		}
		if (!done) {
			break;
		}
	}
}

void final_run(int v1, int v2) {
	prepare(v1);
	optimize(v2);
	prepare(v2);
	optimize(v1);
	cout << "! " << v1 + 1 << ' ' << v2 + 1 << endl;
	exit(0);
}

void dfs_check(int v, int pr) {
	for (int to : e[v]) {
		if (to == pr) {
			continue;
		}
		dfs_check(to, v);
	}
	if (sz(e[v]) == 1 && pr != -1) {
		if (advantage(v) > 0) {
			final_run(root, v);
		}
	}
}

void check() {
	dfs_check(root, -1);
}

int get_distant() {
	int v = root;
	while (cnt[v] > 1) {
		int new_v = -1;
		int new_cnt = 0;
		for (int to : e[v]) {
			if (cnt[to] < cnt[v] && umx(new_cnt, cnt[to])) {
				new_v = to;
			}
		}
		assert(new_v != -1);
		v = new_v;
	}
	return v;
}

void rec(int v) {
	prepare(v);
	if (cnt[v] == 1) {
		return;
	}
	int w = v;
	v = get_distant();
	prepare(v);
	check();
	vi q;
	while (w != v) {
		q.pb(w);
		w = parent[w];
	}
	q.pb(v);
	forn (i, sz(q) - 1) {
		remove_edge(q[i], q[i + 1]);
	}
	for (int to : q) {
		rec(to);
	}
}

int main() {
	cin >> n;
	forn (i, n - 1) {
		int x, y;
		scanf("%d%d", &x, &y);
		--x;
		--y;
		e[x].pb(y);
		e[y].pb(x);
	}
	int v = 0;
	prepare(v);
	v = get_distant();
	prepare(v);
	check();
	rec(v);
	return 0;
}
