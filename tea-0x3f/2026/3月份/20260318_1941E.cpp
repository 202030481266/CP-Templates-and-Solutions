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

static constexpr int MAXN = 100005;
static constexpr int INF = 0x3f3f3f3f;
static constexpr ll LLINF = 0x3f3f3f3f3f3f3f3f;
static constexpr int MOD = 1e9 + 7;


void solve() {
	int n, m, k, d;
	cin >> n >> m >> k >> d;
	vi arr(m + 1);
	vl dp(m + 1);
	vl res;
	vi q(m + 10);
	int ql = 0, qr = 0;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) cin >> arr[j];
		// dp[i] = min(dp[x]), i - x <= d + 1, x >= i - d - 1
		// 维护一个长度为 d + 1的滑窗的最小值，单调队列
		ql = qr = 0; // clear
		dp[1] = 1;
		q[qr++] = 1;
		for (int j = 2; j <= m; ++j) {
			while (ql < qr && q[ql] < j - d - 1) ++ql;
			dp[j] = dp[q[ql]] + arr[j] + 1;
			while (ql < qr && dp[q[qr - 1]] > dp[j]) --qr;
			q[qr++] = j;
		}
		res.push_back(dp[m]);
	}
	ll ans = LLINF;
	ll cur = 0;
	for (int i = 0; i < n; ++i) {
		cur += res[i];
		if (i >= k) cur -= res[i - k];
		if (i >= k - 1) ans = min(ans, cur);
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