// Problem: F. Vasya and Endless Credits
// Contest: Codeforces - Educational Codeforces Round 59 (Rated for Div. 2)
// URL: https://codeforces.com/problemset/problem/1107/F
// Memory Limit: 256 MB
// Time Limit: 3000 ms
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

inline constexpr int  MAXN = 500'005;
inline constexpr int  INF = 0x3f3f3f3f;
inline constexpr ll   LLINF = 0x3f3f3f3f3f3f3f3fLL;
inline constexpr int  MOD = 1'000'000'007;
inline constexpr int  MAXB = 30;

inline constexpr int  INT_INF = numeric_limits<int>::max() / 2;
inline constexpr ll   LL_INF = numeric_limits<ll>::max() / 2;

// guess1: 条件严格，但是n*m还挺大的，时间2s，意味着最后的复杂度是O(n*m)的才对
// guess2: 不能单独的一个维度进行dp，因为会影响形状
// guess3: ans = f[x][y] * g[y][x] for x in [0..n] for y in [0..m]
// guess4: f[x][y] = dp[n][x] * C(n - x, y) ?

inline constexpr int M = 998'244'353;
inline constexpr int N = 3603;
int n, m, k;
int row[N], col[N];
int bone[2401][4];
int f[N][N], g[N][N];

long long fac[N + 1], ifac[N + 1];

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
long long C(int x, int y) {
	if (y > x) return 0;
	return fac[x] * ifac[y] % M * ifac[x - y] % M;
}

void init() {
	fac[0] = 1;
	for (int i = 1; i <= N; i++) fac[i] = fac[i - 1] * i % M;
	ifac[N] = inv(fac[N]);
	for (int i = N - 1; i >= 0; i--) ifac[i] = ifac[i + 1] * (i + 1) % M;
}

void solve() {
	cin >> n >> m >> k;
	init();
	for (int i = 1; i <= k; ++i) {
		cin >> bone[i][0] >> bone[i][1] >> bone[i][2] >> bone[i][3];
		row[bone[i][0]] = row[bone[i][2]] = 1;
		col[bone[i][1]] = col[bone[i][3]] = 1;
	}
	f[0][0] = g[0][0] = 1;
	for (int i = 1; i <= n; ++i) {
		for (int j = 0; 2 * j <= i; ++j) f[i][j] = f[i - 1][j];
		if (i == 1 || row[i] || row[i - 1]) continue;
		for (int j = 1; 2 * j <= i; ++j) f[i][j] = (f[i][j] + f[i - 2][j - 1]) % M;
	}
	for (int i = 1; i <= m; ++i) {
		for (int j = 0; 2 * j <= i; ++j) g[i][j] = g[i - 1][j];
		if (i == 1 || col[i] || col[i - 1]) continue;
		for (int j = 1; 2 * j <= i; ++j) g[i][j] = (g[i][j] + g[i - 2][j - 1]) % M;
	}
	int cr = 0, cc = 0;
	for (int i = 1; i <= n; ++i) cr += row[i] ^ 1;
	for (int i = 1; i <= m; ++i) cc += col[i] ^ 1;
	ll ans = 0;
	for (int x = 0; 2 * x <= cr && x <= cc; ++x) {
		for (int y = 0; 2 * x + y <= cr && 2 * y + x <= cc; ++y) {
			ll cnt_x = 1LL * f[n][x] * C(cr - 2 * x, y) % M;
			ll cnt_y = 1LL * g[m][y] * C(cc - 2 * y, x) % M;
			ans = (ans + cnt_x * cnt_y % M * fac[x] % M * fac[y]) % M;
		}
	}
	cout << ans << '\n';
}


int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t = 1;
	//cin >> t;
	while (t--) solve();
}