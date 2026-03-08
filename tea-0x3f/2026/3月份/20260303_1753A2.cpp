// Problem: A2. Make Nonzero Sum (hard version)
// Contest: Codeforces - Codeforces Round 829 (Div. 1)
// URL: https://codeforces.com/problemset/problem/1753/A2
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


void solve() {
	int n;
	cin >> n;
	vi arr(n + 1);
	int sum = 0;
	for (int i = 1; i <= n; ++i) {
		cin >> arr[i];
		sum += arr[i];
	}
	if (sum % 2) {
		cout << -1 << '\n';
		return;
	}
	int cnt = 0;
	if (sum == 0) {
		cout << n << '\n';
		for (int i = 1; i <= n; ++i) cout << i << ' ' << i << '\n';
		return;
	}
	for (int i = 2; i <= n; ++i) {
		if (arr[i] == (sum < 0 ? -1 : 1)) {
			++cnt;
			++i;
		}
	}
	int half = abs(sum) / 2;
	if (cnt < half) {
		cout << -1 << '\n';
		return;
	}
	vi ans;
	for (int i = 1; i <= n; ++i) {
		ans.push_back(i);
		if (i + 1 <= n && arr[i + 1] == (sum < 0 ? -1 : 1) && half > 0) {
			--half;
			++i;
		}
	}
	int m = ans.size();
	cout << m << '\n';
	for (int i = 0; i < m; ++i) {
		if (i == m - 1) cout << ans[i] << ' ' << min(n, ans[i] + 1) << '\n';
		else cout << ans[i] << ' ' << min(ans[i + 1] - 1, ans[i] + 1) << '\n';
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t = 1;
	cin >> t;
	while (t--) solve();
	return 0;
}