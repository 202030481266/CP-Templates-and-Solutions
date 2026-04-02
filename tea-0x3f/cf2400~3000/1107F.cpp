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

// guess1: 在第c个月贷款，然后收益曲线就是 y = -bi * (x - ci) + ai = -bi * x + bi * ci + ai
// guess2: 最好的方法肯定是连续贷款，中间不会有空缺，不然肯定会有更加好的方案，而且最后的答案肯定也不会超过n，拿完走人了啊
// guess3: 对于第 i 个物品而言， 决策需要的东西：当前已经有的负债表状态，关键是怎么表示？
// guess4: 最佳方案中绝对不会存在一个物品 i，它对于整体的贡献是负的。（我为什么要搬起石头砸自己的脚？）
// guess5: 如果一个物品在d天之内绝对不会亏，要额外的处理，因为这个时候不等式不会成立，价值就不是线性的了，这个时候等价于另外的一种选择模式：
//  - 0, 1, 2, 3, 4, .... d
//  - S = sum(ai) - sum(i * bi) for i in subset s'
//	- S = sum(ai) - sum(i * bi) for i in subset s(a) + sum(ai - bi * ki) for i in subset sb
//  - 对于 d 天而言，实际上划分为两个部分了，首先决策一个 x 天的尾部的贷款，然后就是选择 top(d-x) 可以完全收益的贷款

int n;
ll a[503], b[503], c[503];
ll dp[2][503][503];

void solve() {
	cin >> n;
	for (int i = 1; i <= n; ++i) cin >> a[i] >> b[i] >> c[i];
	vi ids(n);
	iota(ids.begin(), ids.end(), 1);
	ranges::sort(ids, [&](int i, int j) { return b[i] > b[j]; }); // 排序不等式
	int pre = 0, cur = 1;
	ll ans = 0, x = 0;
	for (int i : ids) {
		memset(dp[cur], 0, sizeof(dp[cur]));
		++x;
		for (int j = 1; j <= x; ++j) { // 已经加入的贷款数量
			for (int k = 0; k <= j; ++k) { // 多少个是当前的已经加入的非线性贷款
				if (j - k - 1 >= c[i]) { // 非线性
					dp[cur][j][k] = max(dp[cur][j][k], dp[pre][j][k]);
					if (k > 0 && a[i] > b[i] * c[i]) {
						dp[cur][j][k] = max(dp[cur][j][k], dp[pre][j - 1][k - 1] + a[i] - b[i] * c[i]);
					}
				}
				else { // 线性
					dp[cur][j][k] = max(dp[cur][j][k], dp[pre][j][k]);
					if (j > k && a[i] > b[i] * (j - k - 1)) {
						dp[cur][j][k] = max(dp[cur][j][k], dp[pre][j - 1][k] + a[i] - b[i] * (j - k - 1));
					}
				}
				ans = max(ans, dp[cur][j][k]);
			}
		}
		cout << dp[cur][1][0] << ' ' << dp[cur][2][1] << ' ' << dp[cur][3][1] << endl;
		pre ^= 1;
		cur ^= 1;
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