#ifdef _MSC_VER
#include "pch.h"
#else
#include <bits/stdc++.h>
#endif
#include <format>
#include <concepts>
#include <ranges>

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

inline constexpr int  MAXN = 300005;
inline constexpr int  INF = 0x3f3f3f3f;
inline constexpr ll   LLINF = 0x3f3f3f3f3f3f3f3fLL;
inline constexpr int  MOD_197 = 1'000'000'007;
inline constexpr int  MOD_998 = 998'244'353;
inline constexpr int  MAXB = 30;

// 本质上就是欧拉路径模板题目，和构造有JB关系啊？

struct DSU
{
	vector<int> par, rnk, sz;
	int c;
	DSU(int n) : par(n + 1), rnk(n + 1, 0), sz(n + 1, 1), c(n)
	{
		for (int i = 1; i <= n; ++i)
			par[i] = i;
	}
	int find(int i)
	{
		return (par[i] == i ? i : (par[i] = find(par[i])));
	}
	bool same(int i, int j)
	{
		return find(i) == find(j);
	}
	int get_size(int i)
	{
		return sz[find(i)];
	}
	int count()
	{
		return c; // connected components
	}
	int merge(int i, int j)
	{
		if ((i = find(i)) == (j = find(j)))
			return -1;
		else
			--c;
		if (rnk[i] > rnk[j])
			swap(i, j);
		par[i] = j;
		sz[j] += sz[i];
		if (rnk[i] == rnk[j])
			rnk[j]++;
		return j;
	}
};

void solve() {
	int n;
	cin >> n;

	vp edges(n);
	int mx = 0;
	for (auto& [u, v] : edges) {
		cin >> u >> v;
		mx = max(mx, u);
		mx = max(mx, v);
	}

	vi d(mx + 1);
	for (auto [u, v] : edges) {
		++d[u];
		++d[v];
	}

	vi spec;
	for (int i = 1; i <= mx; ++i) {
		if (d[i] & 1) spec.push_back(i);
	}

	if (spec.size() > 4 || (int)spec.size() & 1) {
		cout << -1 << '\n';
		return;
	}

	vpp g(mx + 1);
	DSU dsu(mx);
	for (int i = 0; i < n; ++i) {
		int u = edges[i].first, v = edges[i].second;
		g[u].emplace_back(v, i);
		g[v].emplace_back(u, i);
		dsu.merge(u, v);
	}

	int tot = 0;
	vi anc;
	for (int i = 1; i <= mx; ++i) {
		if (d[i] && dsu.find(i) == i) {
			++tot;
			anc.push_back(i);
		}
	}

	if (tot > 2) {
		cout << -1 << '\n';
		return;
	}

	vii path;
	vi cur;
	vi vis(n);

	// Hierholzer, O(V + E)
	auto dfs = [&](auto&& self, int u) -> void {
		while (!g[u].empty()) {
			auto [v, eid] = g[u].back();
			g[u].pop_back();
			if (vis[eid]) continue;
			vis[eid] = 1;
			self(self, v);
			cur.push_back(eid);
		}
	};

	auto check = [&](const vi& e) -> bool {
		fill(d.begin(), d.end(), 0);
		for (int eid : e) {
			++d[edges[eid].first];
			++d[edges[eid].second];
		}
		int odd = 0;
		for (int eid : e) {
			int u = edges[eid].first, v = edges[eid].second;
			if (d[u] & 1) {
				d[u] = 0;
				++odd;
			}
			if (d[v] & 1) {
				d[v] = 0;
				++odd;
			}
		}
		return odd == 0 || odd == 2;
	};

	// Start from a odd-degree node
	if (spec.size() <= 2 || spec.size() == 4 && tot == 2) {
		if (spec.size() == 4) {
			// 检查其中是否是两两分布
			int s1 = 0, s2 = 0;
			for (int i : spec) {
				if (dsu.find(i) == anc[0]) ++s1;
				else ++s2;
			}
			if (s1 != 2 || s2 != 2) {
				cout << -1 << '\n';
				return;
			}
		}
		if (spec.size() == 2) {
			// 检查是否分布在同一个无向图
			if (dsu.find(spec[0]) != dsu.find(spec[1])) {
				cout << -1 << '\n';
				return;
			}
		}
		for (int u : spec) {
			cur.clear();
			dfs(dfs, u);
			if (cur.size()) {
				reverse(cur.begin(), cur.end());
				path.push_back(cur);
			}
		}
		for (int i = 1; i <= mx; ++i) {
			if (g[i].size()) {
				cur.clear();
				dfs(dfs, i);
				if (cur.size()) {
					reverse(cur.begin(), cur.end());
					path.push_back(cur);
				}
			}
		}
	}
	else {
		// 1 个连通块 + 4 个奇数的点，无法直接寻找欧拉路径
		// 需要随机游走一段，将其划分为两个欧拉路径，但是需要对每个子图进行欧拉路径存在的判断
		int u = spec[0];
		vi first_path;
		while (g[u].size()) {
			auto [v, eid] = g[u].back();
			g[u].pop_back();
			if (vis[eid]) continue;
			vis[eid] = 1;
			first_path.push_back(eid);
			u = v;
		}
		int x = spec[0], y = first_path.back();
		for (int u : spec) {
			if (u == x || u == y) continue;
			cur.clear();
			dfs(dfs, u);
			if (cur.size()) {
				if (!check(cur)) {
					cout << -1 << '\n';
					return;
				}
				reverse(cur.begin(), cur.end());
				path.push_back(cur);
			}
		}
		for (int eid : first_path) {
			int u = edges[eid].first, v = edges[eid].second;
			vis[eid] = 0;
			g[u].emplace_back(v, eid);
			g[v].emplace_back(u, eid);
		}
		for (int u : spec) {
			if (u != x && u != y) continue;
			cur.clear();
			dfs(dfs, spec[0]);
			if (cur.size()) {
				if (!check(cur)) {
					cout << -1 << '\n';
					return;
				}
				reverse(cur.begin(), cur.end());
				path.push_back(cur);
			}
		}
	}

	// output
	int N = path.size();
	if (N > 2 || N == 0) {
		cout << -1 << '\n';
	}
	else {
		if (N == 1) {
			N = path[0].size();
			if (N < 2) {
				cout << -1 << '\n';
			}
			else {
				// Essentially, it is 1 euler path
				cout << 1 << '\n';
				cout << path[0][0] + 1 << '\n';
				cout << N - 1 << '\n';
				for (int i = 1; i < N; ++i) cout << path[0][i] + 1 << ' ';
			}
		}
		else { // N = 2
			cout << path[0].size() << '\n';
			for (int v : path[0]) cout << v + 1 << ' ';
			cout << '\n';
			cout << path[1].size() << '\n';
			for (int v : path[1]) cout << v + 1 << ' ';
		}
	}
}


int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t = 1;
	while (t--) solve();
	return 0;
}

