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

// guess: 如果一棵树是fib-tree，那么随便删除一个fib[x-1]的fib-tree，得到依然是一个合法的fib-tree
// 可以使用数学归纳法证明

void solve() {
	int n;
	cin >> n;

	vii g(n + 1);
	for (int i = 0, u, v; i < n - 1; ++i) {
		cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}

	vi fib = { 1, 1 };
	while (fib.back() < n) {
		int fz = fib.size();
		fib.push_back(0);
		fib[fz] = fib[fz - 1] + fib[fz - 2];
	}

	if (fib.back() > n) {
		cout << "NO" << '\n';
		return;
	}

	vi idx(n + 1, -1);
	int m = fib.size();
	for (int i = 0; i < m; ++i) idx[fib[i]] = i;

	vi sz(n + 1);
	vi vis(n + 1);
	vi st(n + 1);
	vi ed(n + 1);
	vi order(n + 1);
	vi father(n + 1);
	int tot = 0;

	auto cal = [&](this auto&& self, int u, int fa) -> void {
		st[u] = ++tot;
		order[tot] = u;
		father[u] = fa;
		for (int v : g[u]) {
			if (v != fa) {
				self(v, u);
			}
		}
		ed[u] = tot;
	};

	cal(1, 0);

	auto dfs = [&](this auto&& self, int u, int fa) -> void {
		sz[u] = 1;
		for (int v : g[u]) {
			if (vis[v] || v == fa) continue;
			self(v, u);
			sz[u] += sz[v];
		}
	};

	vi source{ 1 };
	dfs(1, 0);
	for (int i = m - 1; i >= 0; --i) {
		for (int u : source) {
			if (sz[u] > 3) {
				dfs(u, father[u]);
			}
		}
		int N = source.size();
		for (int j = 0; j < N; ++j) {
			int u = source[j];
			if (sz[u] <= 3) continue;
			int p = st[u] + 1;
			int k = idx[sz[u]];
			int flag = 0;
			while (p <= ed[u]) {
				int v = order[p];
				if (vis[v]) {
					p = ed[v] + 1;
					continue;
				}
				if (sz[v] == fib[k - 1] || sz[v] == fib[k - 2]) {
					vis[v] = 1;
					source.push_back(v);
					flag = 1;
					break;
				}
				++p;
			}
			if (!flag) {
				cout << "NO" << '\n';
				return;
			}
		}
	}

	cout << "YES" << '\n';
}


int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t = 1;
	while (t--) solve();
	return 0;
}