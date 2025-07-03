#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;

static constexpr int mod = 1e9 + 7;
static constexpr int maxn = 2e5 + 7;

int pw[maxn];

void solve() {
	int n;
	cin >> n;
	vector<int> cnt(n + 1);
	vector g(n + 1, vector<int>());
	for (int i = 0, u, v; i < n - 1; ++i) {
		cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
		++cnt[u];
		++cnt[v];
	}
	vector<int> leaves;
	for (int i = 2; i <= n; ++i) {
		if (cnt[i] == 1) {
			leaves.push_back(i);
		}
	}
	if (leaves.size() > 2) {
		cout << 0 << '\n';
		return;
	}
	if (leaves.size() <= 1) {
		cout << pw[n] << '\n';
		return;
	}
	vector<int> dep(n + 1), fa(n + 1);
	auto dfs = [&](auto&& self, int u, int father) -> void {
		fa[u] = father;
		dep[u] = dep[father] + 1;
		for (int v : g[u]) {
			if (v != father) {
				self(self, v, u);
			}
		}
		};
	dfs(dfs, 1, 0);
	int x = leaves[0], y = leaves[1];
	if (dep[x] < dep[y]) swap(x, y);
	while (dep[x] > dep[y]) x = fa[x];
	while (x != y) {
		x = fa[x];
		y = fa[y];
	}
	int d1 = dep[leaves[0]] - dep[x], d2 = dep[leaves[1]] - dep[x];
	if (d1 == d2) {
		cout << (2 * pw[n - 2 * d1] % mod) << '\n';
	}
	else {
		d1 = min(d1, d2);
		d2 = max(d1, d2);
		n -= d1 + d2;
		cout << ((pw[n + (d2 - d1 - 1)] + pw[n + (d2 - d1)]) % mod) << '\n';
	}
}


int main() {
	ios::sync_with_stdio(false); cin.tie(nullptr);
	int t;
	cin >> t;
	pw[0] = 1;
	for (int i = 1; i <= 200000; ++i) pw[i] = pw[i - 1] * 2 % mod;
	while (t--) solve();
}
