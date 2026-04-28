// Problem: F. The Chocolate Spree
// Contest: Codeforces - Manthan, Codefest 16
// URL: https://codeforces.com/problemset/problem/633/F
// Memory Limit: 256 MB
// Time Limit: 2000 ms
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

inline constexpr int  MAXN = 100'005;
inline constexpr int  INF = 0x3f3f3f3f;
inline constexpr ll   LLINF = 0x3f3f3f3f3f3f3f3fLL;
inline constexpr int  MOD = 1'000'000'007;
inline constexpr int  MAXB = 30;

inline constexpr int  INT_INF = numeric_limits<int>::max() / 2;
inline constexpr ll   LL_INF = numeric_limits<ll>::max() / 2;


int n;
int arr[MAXN];
ll b1[MAXN], b2[MAXN], b3[MAXN];
vii g(MAXN);

void update(const ll val, ll& x, ll& y, ll& z) {
	if (val > x) {
		z = y;
		y = x;
		x = val;
	}
	else if (val > y) {
		z = y;
		y = val;
	}
	else if (val > z) z = val;
}

void dfs1(int u, int fa) {
	for (int v : g[u]) {
		if (v != fa) {
			dfs1(v, u);
			update(b1[v], b1[u], b2[u], b3[u]);
		}
	}
	b1[u] += arr[u];
	b2[u] += arr[u];
	b3[u] += arr[u];
}

ll f[MAXN], f1[MAXN], f2[MAXN];
ll dp[MAXN];
ll ans = 0;

void cal_f(int u, int fa) {
	for (int v : g[u]) {
		if (v != fa) {
			cal_f(v, u);
			if (f[v] > f1[u]) {
				f2[u] = f1[u];
				f1[u] = f[v];
			}
			else if (f[v] > f2[u]) f2[u] = f[v];
		}
	}
	f[u] = max(b1[u] + b2[u] - arr[u], f1[u]);
}

void dfs2(int u, int fa, ll mx) {
    for (int v : g[u]) {
        if (v != fa) {
            dp[v] = dp[u] + arr[v];
            if (b1[v] + arr[u] == b1[u]) {
                dp[v] = max(dp[v], b2[u] + arr[v]);
            }
            else {
                dp[v] = max(dp[v], b1[u] + arr[v]);
            }
            ll y = 0;
            if (b1[v] + arr[u] == b1[u]) {
                y = max(y, max(b2[u] + b3[u] - arr[u], dp[u] + b2[u] - arr[u]));
            }
            else if (b1[v] + arr[u] == b2[u]) {
                y = max(y, max(b1[u] + b3[u] - arr[u], dp[u] + b1[u] - arr[u]));
            }
            else {
            	y = max(y, max(b1[u] + b2[u] - arr[u], dp[u] + b1[u] - arr[u]));
            }
            if (f[v] == f1[u]) y = max(y, f2[u]);
            else y = max(y, f1[u]);
            y = max(y, mx);
            ans = max(ans, f[v] + y);
            dfs2(v, u, y);
        }
    }
}

void solve() {
	cin >> n;
	for (int i = 1; i <= n; ++i) cin >> arr[i];
	for (int i = 0, u, v; i < n - 1; ++i) {
		cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
    dfs1(1, 0);
    cal_f(1, 0);
    dfs2(1, 0, 0);
    cout << ans << '\n';
}


int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	solve();
}
