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

// 给定 n 个物品，有两个限制，一个是重量一个是类型，还需要考虑顺序
// 本质上最为关键的是求解出来有多少个不同的组合，以及组合所得到的集合大小
// dp[x][y][z][m] = dp[x-1][y][z][m-a[i]] * (y+z-x+1) if b[i]==1
// 1 3 1，如果商品出现的顺序是 1 1 3，好像就没有方案了？
// 上面的dp有问题，不能依赖于顺序
// 比方说一个组合是(4,3,1)三元组，那么总共不同的摆放有多少种？
// 然后说组合为(4,3,1)且重量为x的方法有多少种，这里不需要关心顺序
// f[x][y][z][t] = f[x-1][y][z][s] if s != t && t == 1
// 超时了，需要剪枝, O(n^4 * m)实际上可以划分计算，然后使用一个m
// 考虑分治，O(n^3 * m) 计算两个物品的，然后O(n^2*m)计算另外一个物品，组合计算枚举重量，O(n^3 * m)即可

ll f[26][26][26][4];
ll g[26][26][26];
int dp1[26][26][2501];
int dp2[26][2501];

void solve() {
	int n, m;
	cin >> n >> m;
	vi a(n + 1), b(n + 1);
	for (int i = 1; i <= n; ++i) cin >> a[i] >> b[i];
	int h = (n + 1) / 2;
	dp1[0][0][0] = 1;
	dp2[0][0] = 1;
	for (int i = 1; i <= n; ++i) {
		if (b[i] == 3) continue;
		for (int x = h; x >= 0; --x) {
			for (int y = h; y >= 0; --y) {
				for (int c = m; c >= a[i]; --c) {
					if (b[i] == 1) {
						if (x > 0) dp1[x][y][c] = (dp1[x][y][c] + dp1[x - 1][y][c - a[i]]) % MOD;
					}
					else {
						if (y > 0) dp1[x][y][c] = (dp1[x][y][c] + dp1[x][y - 1][c - a[i]]) % MOD;
					}
				}
			}
		}
	}
	for (int i = 1; i <= n; ++i) {
		if (b[i] != 3) continue;
		for (int x = h; x >= 1; --x) {
			for (int c = m; c >= a[i]; --c) dp2[x][c] = (dp2[x][c] + dp2[x - 1][c - a[i]]) % MOD;
		}
	}
	f[1][0][0][1] = f[0][1][0][2] = f[0][0][1][3] = 1;
	for (int x = 0; x <= h; ++x) {
		for (int y = 0; y <= h; ++y) {
			for (int z = 0; z <= h; ++z) {
				int mx = (x > y) ? ((x > z) ? x : z) : ((y > z) ? y : z);
				int sum = x + y + z;
				if (2 * mx - 1 > sum) continue; // 肯定摆不出来
				if (x > 0) f[x][y][z][1] += x * (f[x - 1][y][z][2] + f[x - 1][y][z][3]);
				if (y > 0) f[x][y][z][2] += y * (f[x][y - 1][z][1] + f[x][y - 1][z][3]);
				if (z > 0) f[x][y][z][3] += z * (f[x][y][z - 1][1] + f[x][y][z - 1][2]);
				for (int i = 1; i <= 3; ++i) {
					f[x][y][z][i] %= MOD;
					g[x][y][z] += f[x][y][z][i];
				}
			}
		}
	}
	ll ans = 0;
	for (int x = 0; x <= h; ++x) {
		for (int y = 0; y <= h; ++y) {
			for (int z = 0; z <= h; ++z) {
				int mx = (x > y) ? ((x > z) ? x : z) : ((y > z) ? y : z);
				int sum = x + y + z;
				if (2 * mx - 1 > sum) continue; // 肯定摆不出来
				for (int pre = 0; pre <= m; ++pre) {
					ans += 1LL * dp1[x][y][pre] * dp2[z][m - pre] % MOD * g[x][y][z] % MOD;
				}
				ans %= MOD;
			}
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