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
inline constexpr int  MOD = 1'000'000'007;
inline constexpr int  MAXB = 30;


std::vector<int> getDiameter(const std::vector<std::vector<int>>& g) {
	int n = (int)g.size() - 1;
	if (n <= 0) return {};

	std::vector<int> q(n);
	std::vector<int> pre(n + 1);

	auto get_farthest = [&](int start) {
		int head = 0, tail = 0;
		q[tail++] = start;
		pre[start] = -1;
		int farthest = start;

		while (head < tail) {
			int u = q[head++];
			farthest = u;
			for (int v : g[u]) {
				if (v != pre[u]) {
					pre[v] = u;
					q[tail++] = v;
				}
			}
		}
		return farthest;
	};

	int S = get_farthest(1);
	int T = get_farthest(S);

	std::vector<int> path;
	for (int u = T; u != -1; u = pre[u]) {
		path.push_back(u);
	}

	return path;
}

std::vector<int> bfs(int src, const vii& g, int n) {
	vector<int> dist(n + 1, -1);
	queue<int> q;
	dist[src] = 0;
	q.push(src);
	int farthest = src;
	while (!q.empty()) {
		int u = q.front(); q.pop();
		for (int v : g[u]) {
			if (dist[v] == -1) {
				dist[v] = dist[u] + 1;
				q.push(v);
				if (dist[v] > dist[farthest]) farthest = v;
			}
		}
	}
	return dist;
}


void solve() {
	int n;
	cin >> n;
	vii g(n + 1);
	for (int i = 0, u, v; i < n - 1; ++i) {
		cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}

	auto path = getDiameter(g);
	int m = path.size();

	vi b(n + 1);
	for (int v : path) b[v] = 1;

	auto d1 = bfs(path[0], g, n);
	auto d2 = bfs(path[m - 1], g, n);

	ll ans = 0;
	
	vector<tuple<int, int, int>> res;
	auto dfs = [&](auto&& self, int u, int fa) -> void {
		for (int v : g[u]) {
			if (v != fa) {
				self(self, v, u);
			}
		}
		if (!b[u]) {
			if (d1[u] > d2[u]) {
				ans += d1[u];
				res.emplace_back(u, path[0], u);
			}
			else {
				ans += d2[u];
				res.emplace_back(u, path[m - 1], u);
			}
		}
	};
	dfs(dfs, path[0], 0);

	for (int i = 0; i < m - 1; ++i) {
		ans += d2[path[i]];
		res.emplace_back(path[i], path[m - 1], path[i]);
	}

	cout << ans << '\n';
	for (auto [u, v, w] : res) cout << u << ' ' << v << ' ' << w << '\n';
}


int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t = 1;
	while (t--) solve();
	return 0;
}