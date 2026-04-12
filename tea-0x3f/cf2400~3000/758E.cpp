// Problem: E. Broken Tree
// Contest: Codeforces - Codeforces Round 392 (Div. 2)
// URL: https://codeforces.com/problemset/problem/758/E
// Memory Limit: 256 MB
// Time Limit: 4000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#ifdef _MSC_VER
#include "pch.h"
#else
#include <bits/stdc++.h>
#endif

#include <format>       // std::format
#include <concepts>     // concepts
#include <ranges>       // std::ranges

using namespace std;

using ll = long long;
using ull = unsigned long long;
using uint = unsigned int;
using ld = long double;

template<typename T, typename U = T>
using pr = pair<T, U>;

template<typename T>
using vec = vector<T>;

using pii = pr<int>;
using pll = pr<ll>;
using vi = vec<int>;
using vl = vec<ll>;
using vii = vec<vi>;
using vll = vec<vl>;
using vp = vec<pii>;
using vpp = vec<vp>;

template<typename T>
concept Printable = requires(T x) { cerr << x; };

template<typename T>
concept PairLike = requires(T x) { x.first; x.second; };

template<typename T>
concept Iterable = ranges::range<T> && !PairLike<T> && !is_convertible_v<T, string_view>;

template<typename T> void __print(const T&);

void __print(char x) { cerr << '\'' << x << '\''; }
void __print(bool x) { cerr << (x ? "true" : "false"); }
void __print(const char* x) { cerr << '"' << x << '"'; }
void __print(const string& x) { cerr << '"' << x << '"'; }
void __print(string_view x) { cerr << '"' << x << '"'; }
template<Printable T>
	requires (!PairLike<T> && !Iterable<T>
&& !is_same_v<T, char>
&& !is_same_v<T, bool>
&& !is_same_v<T, string>
&& !is_same_v<T, string_view>
&& !is_convertible_v<T, const char*>)
void __print(const T& x) { cerr << x; }

template<PairLike T>
void __print(const T& x) {
	cerr << '{';
	__print(x.first);
	cerr << ", ";
	__print(x.second);
	cerr << '}';
}

template<typename... Ts>
void __print(const tuple<Ts...>& t) {
	cerr << '(';
	apply([&]<typename... Args>(const Args&... args) {
		size_t n = 0;
		((cerr << (n++ ? ", " : ""), __print(args)), ...);
	}, t);
	cerr << ')';
}

template<Iterable T>
void __print(const T& x) {
	cerr << '{';
	bool first = true;
	for (const auto& i : x) {
		if (!first) cerr << ", ";
		__print(i);
		first = false;
	}
	cerr << '}';
}

template<typename T>
void __print(const optional<T>& x) {
	if (x) { cerr << "Some("; __print(*x); cerr << ')'; }
	else     cerr << "None";
}

void _print() { cerr << "]\n"; }

template<typename T, typename... V>
void _print(T&& t, V&&... v) {
	__print(t);
	if constexpr (sizeof...(v) > 0) cerr << ", ";
	_print(forward<V>(v)...);
}

#ifndef ONLINE_JUDGE
#   define debug(...) \
        cerr << std::format("[{}:{}] [{}] = [", __FILE_NAME__, __LINE__, #__VA_ARGS__); \
        _print(__VA_ARGS__)
#else
#   define debug(...)
#endif

inline constexpr int  MAXN = 200'005;
inline constexpr int  INF = 0x3f3f3f3f;
inline constexpr ll   LLINF = 0x3f3f3f3f3f3f3f3fLL;
inline constexpr int  MOD = 1'000'000'007;
inline constexpr int  MAXB = 30;

inline constexpr int  INT_INF = numeric_limits<int>::max() / 2;
inline constexpr ll   LL_INF = numeric_limits<ll>::max() / 2;

// guess1: 4 seconds，说明允许较大常数的解法
// guess2: 如果存在一个边的强度小于其子树的边的个数(size - 1)，肯定不行了
// guess3: 可行性判断似乎是较为简单的，每一个边都尽量降低weight就行了，对于x而言，如果strength足够，那么降低到最低的要求
// guess4: 保证最大的weight sum？从guess3的情况出发，从上到下贪心增加即可
// guess5: u -> v, 假设 u 能够增加的限制是 limit[u], 那么 limit[v] = min(add[u], limit[u] - add[u])，限制至少减半或者保持不变

int n;

struct Edge {
	int v, w, s, id;
	Edge() : v(0), w(0), s(0), id(0) {}
	Edge(int _v, int _w, int _s, int _id) : v(_v), w(_w), s(_s), id(_id) {}
};

vec<Edge> g[MAXN];

ll sum[MAXN], delta[MAXN];
int cannot;

void dfs1(int u) {
	if (cannot) return;
	for (Edge& e : g[u]) {
		dfs1(e.v);
		sum[u] += sum[e.v];
		if (e.s >= sum[e.v]) {
			int d = min(e.s - sum[e.v], e.w - 1ll);
			delta[e.id] = d;
			e.s -= d;
			e.w -= d;
			sum[u] += e.w;
		}
		else {
			cannot = 1;
			return;
		}
	}
}

ll dfs2(int u, ll limit) {
	ll use = 0;
	for (Edge& e : g[u]) {
		if (limit <= 0) break;
		int can_add = min(limit, delta[e.id]);
		e.w += can_add;
		e.s += can_add;
		ll next_limit = min(limit - can_add, e.s - sum[e.v]);
		ll tot = dfs2(e.v, next_limit);
		limit -= tot + can_add;
		use += tot + can_add;
	}
	return use;
}

pii edges[MAXN];
int ews[MAXN], ess[MAXN];

void collect(int u) {
	for (Edge& e : g[u]) {
		ews[e.id] = e.w;
		ess[e.id] = e.s;
		collect(e.v);
	}
}

void solve() {
	int n;
	cin >> n;
	for (int i = 0, u, v, w, s; i < n - 1; ++i) {
		cin >> u >> v >> w >> s;
		edges[i].first = u;
		edges[i].second = v;
		g[u].emplace_back(v, w, s, i);
	}
	dfs1(1);
	if (cannot) {
		cout << -1 << '\n';
		return;
	}
	cout << n << '\n';
	dfs2(1, LL_INF);
	collect(1);
	for (int i = 0; i < n - 1; ++i) {
		cout << edges[i].first << ' ' << edges[i].second << ' ' << ews[i] << ' ' << ess[i] << '\n';
	}
}


int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t = 1;
	// cin >> t;
	while (t--) solve();
}