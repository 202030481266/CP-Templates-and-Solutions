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

// guess1: n <= 500, 2s, 最后应该就是 O(n^3) 的复杂度
// guess2: 操作2，4都是没有用的，操作3最多执行一次，其他全部使用操作1即可
// guess3: 对于一个固定w,b棋盘，最小步数是确定的，而且每次操作不会重复
// guess4: 怎么快速计算翻转后的需要的步数?

inline constexpr int N = 503;

int n, m;
int a[N][N], sum[N][N], b[N][N];

void cal() {
	for (int i = n; i >= 1; --i) {
		for (int j = m; j >= 1; --j) {
			int c = a[i][j];
			if (i + 1 <= n) c ^= a[i + 1][j];
			if (j + 1 <= m) c ^= a[i][j + 1];
			if (i + 1 <= n && j + 1 <= m) c ^= a[i + 1][j + 1];
			b[i][j] = c & 1;
			sum[i][j] = sum[i + 1][j] + sum[i][j + 1] - sum[i + 1][j + 1] + b[i][j];
		}
	}
}

void solve() {
	cin >> n >> m;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			char c;
			cin >> c;
			if (c == 'B') a[i][j] = 1;
		}
	}
	cal();
	int ans = sum[1][1];
	int delta = a[n][m] ? -1 : 1;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			int res = sum[1][1] + delta;
			if (i > 1) {
				for (int k = j; k <= m; ++k) {
					int c = a[i - 1][k];
					c ^= a[i][k] ^ 1;
					if (k + 1 <= m) c ^= a[i - 1][k + 1] ^ a[i][k + 1] ^ 1;
					res += (c & 1) - b[i - 1][k];
				}
			}
			if (j > 1) {
				for (int k = i; k <= n; ++k) {
					int c = a[k][j - 1];
					c ^= a[k][j] ^ 1;
					if (k + 1 <= n) c ^= a[k + 1][j - 1] ^ a[k + 1][j] ^ 1;
					res += (c & 1) - b[k][j - 1];
				}
			}
			if (i > 1 && j > 1) {
				int c = a[i - 1][j - 1];
				c ^= a[i][j - 1] ^ a[i - 1][j] ^ a[i][j] ^ 1;
				res += (c & 1) - b[i - 1][j - 1];
			}
			if (res + 3 < ans) ans = res + 3;
		}
	}
	cout << ans << '\n';
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t = 1;
	// cin >> t;
	while (t--) solve();
}