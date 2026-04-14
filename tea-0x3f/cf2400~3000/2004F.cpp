// Problem: F. Make a Palindrome
// Contest: Codeforces - Educational Codeforces Round 169 (Rated for Div. 2)
// URL: https://codeforces.com/problemset/problem/2004/F
// Memory Limit: 512 MB
// Time Limit: 5000 ms
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

// guess1: n <= 2000, 应该是平方的复杂度, O(n^2)，上限是 5s
// guess2: n长度的子数组最多需要n-1次合并或者n-1次分解
// guess3: 无论哪一种操作都会改变数组和，但是最后的回文串是有规律的，所以本质上最后的长度不是重要的，和是重要的
// guess4: 类似于这种 [2, 4, 7] 和 [3, 2, 8] ，只有总和一致的两段，让他俩形成回文串的两段，那么最好的方法就是合并，耗费 (n + m - 2) 步数
// guess5: 类似于guess4，如果总和不能够相等，那么就需要分类讨论
// guess5-1: 如果是偶数，那么肯定可以分为两半，需要1刀切开，然后变成 (n + 1) 个数字，因为有一个空隙不需要合并，那么合并需要 (n - 1) 次合并
// guess5-2: 如果是奇数，说明最好的做法就是 n - 1次合并，不用想了


const int N = 2005;
int a[N];
long long P[N];
short ans_x[N][N], ans_y[N][N];
int dp[N][N];

struct PairSum {
	long long sum;
	short i, j;
	bool operator<(const PairSum& other) const {
		if (sum != other.sum) return sum < other.sum;
		return i < other.i;
	}
};

void solve() {
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		P[i] = P[i - 1] + a[i];
	}
	for (int i = 0; i <= n; i++) {
		for (int j = 0; j <= n; j++) {
			ans_x[i][j] = -1;
			ans_y[i][j] = -1;
		}
	}
	vector<PairSum> pairs;
	pairs.reserve((n + 1) * (n + 2) / 2);
	for (short i = 0; i <= n; i++) {
		for (short j = i; j <= n; j++) {
			pairs.push_back({ P[i] + P[j], i, j });
		}
	}
	sort(pairs.begin(), pairs.end());
	for (size_t k = 0; k < pairs.size(); ) {
		size_t end_k = k;
		while (end_k < pairs.size() && pairs[end_k].sum == pairs[k].sum) end_k++;

		for (size_t m = k; m < end_k - 1; m++) {
			short l_minus_1 = pairs[m].i;
			short r = pairs[m].j;
			short x = pairs[m + 1].i;
			short y_minus_1 = pairs[m + 1].j;

			if (l_minus_1 < r) {
				int l = l_minus_1 + 1;
				ans_x[l][r] = x;
				ans_y[l][r] = y_minus_1 + 1;
			}
		}
		k = end_k;
	}
	int ans = 0;
	for (int len = 1; len <= n; len++) {
		for (int i = 1; i + len - 1 <= n; i++) {
			int j = i + len - 1;
			dp[i][j] = j - i;
			if (ans_x[i][j] != -1 && ans_y[i][j] != -1) {
				int x = ans_x[i][j];
				int y = ans_y[i][j];
				int next_val = 0;
				if (x + 1 <= y - 1) {
					next_val = dp[x + 1][y - 1];
				}
				int cost = (x - i) + (j - y);
				dp[i][j] = min(dp[i][j], next_val + cost);
				ans += dp[i][j];
			}
		}
	}
	cout << ans << '\n';
}


int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t = 1;
	cin >> t;
	while (t--) solve();
}