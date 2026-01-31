// https://codeforces.com/problemset/problem/1209/D
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

static constexpr int inf = 0x3f3f3f3f;
static constexpr int maxn = 2e5 + 7;

int n, m;


int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n >> m;
	vector g(n + 1, vector<int>{});
	set<pair<int, int>> s;
	int ans = 0;
	for (int i = 0, u, v; i < m; ++i) {
		cin >> u >> v;
		if (u > v) swap(u, v);
		if (s.find({ u, v }) == s.end()) {
			s.emplace(u, v);
			g[u].push_back(v);
			g[v].push_back(u);
		}
	}
	vector<int> vis(n + 1);
	
	int node = 0;
	auto dfs = [&](auto&& self, int u) -> void {
		vis[u] = 1;
		++node;
		for (int v : g[u]) {
			if (!vis[v]) {
				self(self, v);
			}
		}
		};

	for (int i = 1; i <= n; ++i) {
		if (!vis[i]) {
			node = 0;
			dfs(dfs, i);
			ans += node - 1;
		}
	}
	cout << (m - ans) << '\n';
}