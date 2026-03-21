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

// 160 factors, 166320
// 首先需要知道的是，如果一个数字不是 x 的因数，那么绝无可能会被参与到一个子序列中，这是一个最重要的观察
// 所以剩下的都是 x 的因数
// 做法就是贪心，这个可以证明，一个分段长的总是不会输给短的
// 现在的做法核心就是给一堆数字，然后判断能不能够形成x了, 根据第一个观察，我们可以维护现在能够形成的所有 x 的因数的集合
// 复杂度 O(n * 160) 最多
int a[MAXN];
int have[MAXN];

void solve() {
	int n, x;
	cin >> n >> x;
	vi arr(n);
	for (int& v : arr) cin >> v;
	vi factors;
	for (int i = 1; i * i <= x; ++i) {
		if (x % i == 0) {
			factors.push_back(i);
			if (x / i != i) factors.push_back(x / i);
		}
	}
	for (int v : factors) a[v] = 1;
	vi cur{ 1 };
	int ans = 0;
	have[1] = 1;
	for (int i = 0; i < n; ++i) {
		if (!a[arr[i]]) continue;
		vi nxt;
		int flag = 0;
		for (int v : cur) {
			ll t = 1LL * v * arr[i];
			if (t > x || !a[t]) continue;
			if (t == x) {
				++ans;
				flag = 1;
				for (int v : cur) have[v] = 0;
				cur = vi{ arr[i], 1 };
				have[arr[i]] = have[1] = 1;
				break;
			}
			nxt.push_back(t);
		}
		if (!flag) {
			for (int v : nxt) {
				if (have[v]) continue;
				have[v] = 1;
				cur.push_back(v);
			}
		}
	}
	cout << ans + 1 << '\n';
	for (int v : factors) a[v] = have[v] = 0;
}


int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t = 1;
	cin >> t;
	while (t--) solve();
}