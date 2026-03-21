// Problem: E. Velepin and Marketing
// Contest: Codeforces - Codeforces Round 852 (Div. 2)
// URL: https://codeforces.com/problemset/problem/1793/E
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#ifdef _MSC_VER
#include "pch.h"
#else
#include <bits/stdc++.h>
#endif

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int uint;
typedef std::pair<int, int> pii;
typedef std::vector<int> vi;
typedef std::vector<vector<int>> vii;
typedef std::vector<ll> vl;
typedef std::vector<vector<ll>> vll;

void __print(int x) { cerr << x; }
void __print(long x) { cerr << x; }
void __print(long long x) { cerr << x; }
void __print(unsigned x) { cerr << x; }
void __print(unsigned long x) { cerr << x; }
void __print(unsigned long long x) { cerr << x; }
void __print(float x) { cerr << x; }
void __print(double x) { cerr << x; }
void __print(long double x) { cerr << x; }
void __print(char x) { cerr << '\'' << x << '\''; }
void __print(const char* x) { cerr << '\"' << x << '\"'; }
void __print(const string& x) { cerr << '\"' << x << '\"'; }
void __print(bool x) { cerr << (x ? "true" : "false"); }

template<typename T, typename V>
void __print(const pair<T, V>& x) { cerr << '{'; __print(x.first); cerr << ','; __print(x.second); cerr << '}'; }
template<typename T>
void __print(const T& x) { int f = 0; cerr << '{'; for (auto& i : x) cerr << (f++ ? "," : ""), __print(i); cerr << "}"; }
void _print() { cerr << "]\n"; }
template <typename T, typename... V>
void _print(T t, V... v) { __print(t); if (sizeof...(v)) cerr << ", "; _print(v...); }

#ifndef ONLINE_JUDGE
#define debug(...) cerr << "[" << #__VA_ARGS__ << "] = ["; _print(__VA_ARGS__)
#else
#define debug(...)
#endif

static constexpr int MAXN = 200005;
static constexpr int INF = 0x3f3f3f3f;
static constexpr ll LLINF = 0x3f3f3f3f3f3f3f3f;
static constexpr int MOD = 1e9 + 7;

// 任何一个方案，使用集合 S 表示选取的人的分配，如果存在 x 属于 S，但是存在 y, 并且 a[y] <= a[x]，那么将x得到的书分配给 y 总是不坏的
// 难以满足的人两种用处: 一种是用来填充当前的分配不足，一种是用来消耗当前的种类
// 考虑二分， 二分开心的人的位置，然后判断是否可以实现，如何判断能够成立似乎不简单
// 但是因为值域不大，完全可以记录对应的最大的位置

void solve() {
	int n;
	cin >> n;
	vi arr(n + 1);
	for (int i = 1; i <= n; ++i) cin >> arr[i];
	ranges::sort(arr);
	int q;
	cin >> q;
	vector<pii> qs;
	for (int i = 0, x; i < q; ++i) {
		cin >> x;
		qs.emplace_back(x, i);
	}
	ranges::sort(qs);
	vi ans(q);
	vi dp(n + 1, -1);
	vi pref_mx(n + 1, 0);
	dp[0] = 0;
	// dp[i]: 恰好划分的最大组数
	// dp[i] = max(dp[j]) + 1, j <= i - arr[i], 最大的几个肯定放到一起最好，前面放不下的本质上都可以放到这个堆里面
	for (int i = 1; i <= n; ++i) { // greedy + dp
		if (i - arr[i] >= 0) {
			dp[i] = pref_mx[i - arr[i]] + 1;
		}
		pref_mx[i] = max(pref_mx[i - 1], dp[i]);
	}
	// 开始贪心的核心逻辑
	vi f(n + 1, 0);
	for (int i = 1; i <= n; ++i) {
		int val = -1;
		if (arr[i] > i) val = n - i - (arr[i] - i) + 1;
		else {
			if (dp[i] > 0) val = dp[i] + n - i;
		}
		if (val >= 0) f[val] = max(f[val], i);
	}
	vi b;
	for (int i = 1; i <= n; ++i) {
		if (f[i] > 0) b.push_back(i);
	}
	for (int i = 0; i < q; ++i) {
		if (i == 0 || qs[i].first != qs[i - 1].first) {
			auto it = lower_bound(b.begin(), b.end(), qs[i].first);
			if (it != b.end()) ans[qs[i].second] = f[*it];
		}
		else ans[qs[i].second] = ans[qs[i - 1].second];
	}
	for (int i = 0; i < q; ++i) cout << ans[i] << '\n';
}


int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t = 1;
	// cin >> t;
	while (t--) solve();
}