// https://codeforces.com/problemset/problem/2114/E
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int n;

void solve() {
	cin >> n;
	vector<int> a(n + 1);
	for (int i = 1; i <= n; ++i) cin >> a[i];
	vector g(n + 1, vector<int>());
	for (int i = 1, u, v; i < n; ++i) {
		cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	vector dp(n + 1, vector<ll>(2));
	auto dfs = [&](auto&& self, int u, int fa) -> void {
		dp[u][0] = a[u];
		dp[u][1] = -a[u];
		if (fa) {
			dp[u][0] = max(dp[u][0], dp[fa][1] + a[u]);
			dp[u][1] = max(dp[u][1], dp[fa][0] - a[u]);
		}
		for (int v : g[u]) {
			if (v != fa) self(self, v, u);
		}
		};
	dfs(dfs, 1, 0);
	for (int i = 1; i <= n; ++i) {
		cout << dp[i][0] << (i == n ? '\n' : ' ');
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while (t--) {
		solve();
	}
}