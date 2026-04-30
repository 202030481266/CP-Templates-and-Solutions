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

inline constexpr int  MAXN = 300'005;
inline constexpr int  INF = 0x3f3f3f3f;
inline constexpr ll   LLINF = 0x3f3f3f3f3f3f3f3fLL;
inline constexpr int  MOD = 1'000'000'007;
inline constexpr int  MAXB = 30;

inline constexpr int  INT_INF = numeric_limits<int>::max() / 2;
inline constexpr ll   LL_INF = numeric_limits<ll>::max() / 2;

inline constexpr int M = 998'244'353;

long long fac[MAXN], ifac[MAXN];

int n, m;

long long quick_power(long long a, long long b, int p) {
	long long ans = 1 % p;
	for (; b; b >>= 1) {
		if (b & 1) ans = ans * a % p;
		a = a * a % p;
	}
	return ans;
}
long long inv(long long x, int p = M) {
	return quick_power(x, p - 2, p) % M;
}
long long binomial(int x, int y) {
	if (y > x) return 0ll;
	return fac[x] * ifac[y] % M * ifac[x - y] % M;
}

void init() {
	fac[0] = 1;
	for (int i = 1; i <= n; i++) fac[i] = fac[i - 1] * i % M;
	ifac[n] = inv(fac[n]);
	for (int i = n - 1; i >= 0; i--) ifac[i] = ifac[i + 1] * (i + 1) % M;
}

void solve() {
	cin >> n >> m;

	init();

	vi left(n + 1), right(n + 1);
	for (int i = 1; i <= n; ++i) cin >> left[i] >> right[i];

	vii g(n + 1);
	for (int i = 1, u, v; i <= m; ++i) {
		cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}

	vi vis(n + 1);
	vi dfn(n + 1);
	vi adj(30);
	vii groups;

	auto dfs = [&](auto&& self, int u, vi& cur) -> void {
		vis[u] = 1;
		cur.push_back(u);
		for (int v : g[u]) {
			if (!vis[v]) self(self, v, cur);
		}
	};

	// 只是遍历其中的大于1大小的无向图
	for (int i = 1; i <= n; ++i) {
		if (!vis[i] && !g[i].empty()) {
			groups.push_back({});
			auto& cur = groups.back();
			dfs(dfs, i, cur);
		}
	}

	vll cnt(n + 1, vl(3 * m + 2));
	vi offset(groups.size());
	// 居然要手动管理内存？crazy?
	for (int i = 1; i < groups.size(); ++i) {
		offset[i] += offset[i - 1] + groups[i - 1].size();
	}

	auto search = [&](auto&& self, int p, int mask, int l, int r, int gid) -> void {
		if (p == groups[gid].size()) {
			int ones = popcount(1u * mask);
			if (ones) {
				++cnt[l][offset[gid] + ones];
				if (r + 1 <= n) --cnt[r + 1][offset[gid] + ones];
			}
			return;
		}
		self(self, p + 1, mask, l, r, gid);
		int nl = max(l, left[groups[gid][p]]);
		int nr = min(r, right[groups[gid][p]]);
		if ((mask & adj[p]) == 0 && nl <= nr) {
			self(self, p + 1, mask | 1 << p, nl, nr, gid);
		}
	};

	for (int gid = 0; gid < groups.size(); ++gid) {
		auto& gr = groups[gid];
		int N = gr.size();
		for (int i = 0; i < N; ++i) dfn[gr[i]] = i;
		for (int i = 0; i < N; ++i) {
			adj[i] = 0;
			for (int v : g[gr[i]]) {
				adj[i] |= 1 << dfn[v];
			}
		}
		search(search, 0, 0, -INF, INF, gid);
	}

	vll dp(n + 1, vl(2 * m + 1));
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= 2 * m; ++j) cnt[i][j] += cnt[i - 1][j];
		dp[i][0] = 1;
		for (int j = 0; j < groups.size(); ++j) {
			for (int V = min(2 * m, i); V >= 1; --V) {
				for (int k = 1; k <= min(V, (int)groups[j].size()); ++k) {
					if (cnt[i][offset[j] + k]) {
						dp[i][V] = (dp[i][V] + dp[i][V - k] * cnt[i][offset[j] + k]) % M;
					}
				}
			}
		}
	}
	vl c(n + 1);
	for (int i = 1; i <= n; ++i) {
		if (g[i].empty()) {
			++c[left[i]];
			if (right[i] + 1 <= n) --c[right[i] + 1];
		}
	}
	ll ans = 0;
	for (int i = 1; i <= n; ++i) c[i] += c[i - 1];
	for (int i = 1; i <= n; ++i) {
		for (int j = 0; j <= min(2 * m, i); ++j) {
			ans = (ans + dp[i][j] * binomial(c[i], i - j) % M) % M;
		}
	}
	cout << ans << '\n';
}


int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t = 1;
	while (t--) solve();
}