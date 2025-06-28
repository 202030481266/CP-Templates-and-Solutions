// https://codeforces.com/problemset/problem/1866/K
// #include "stdafx.h"
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

static constexpr int maxn = 100005;

ll ceil(ll x, ll y) {
	return (x + y - 1) / y;
}

void solve() {
	int n, m;
	cin >> n;
	vector g(n + 1, vector<pii>());
	vector qs(n + 1, vector<pii>());
	for (int i = 1, u, v, w; i < n; ++i) {
		cin >> u >> v >> w;
		g[u].emplace_back(v, w);
		g[v].emplace_back(u, w);
	}
	cin >> m;
	vector<ll> ans(m);
	for (int i = 0, u, x; i < m; ++i) {
		cin >> u >> x;
		qs[u].push_back({ x, i });
	}
	for (int i = 1; i <= n; ++i) {
		if (qs[i].size()) {
			sort(qs[i].begin(), qs[i].end());
		}
	}
	vector<ll> dp1(n + 1), dp2(n + 1), f(n + 1), father(n + 1);
	auto dfs1 = [&](auto&& self, int u, int fa) -> void {
		father[u] = fa;
		for (auto [v, w] : g[u]) {
			if (v != fa) {
				self(self, v, u);
				if (dp1[v] + w > dp1[u]) {
					dp2[u] = dp1[u];
					dp1[u] = dp1[v] + w;
				}
				else if (dp1[v] + w > dp2[u]) {
					dp2[u] = dp1[v] + w;
				}
			}
		}
		};
	dfs1(dfs1, 1, 0);
	auto dfs2 = [&](auto&& self, int u, int fa) -> void {
		for (auto [v, w] : g[u]) {
			if (v != fa) {
				if (dp1[u] == w + dp1[v]) {
					f[v] = max(f[v], max(f[u] + w, w + dp2[u]));
				}
				else {
					f[v] = max(f[v], max(f[u] + w, w + dp1[u]));
				}
				self(self, v, u);
			}
		}
		};
	dfs2(dfs2, 1, 0);
	for (int u = 1; u <= n; ++u) {
		if (qs[u].size()) {
			vector<array<ll, 2>> a;
			for (auto [v, w] : g[u]) {
				if (v == father[u]) {
					a.push_back({ w, f[u] - w });
				}
				else {
					a.push_back({ w, dp1[v] });
				}
			}
			sort(a.begin(), a.end(), [&](const auto& x, const auto& y) {
				return x[0] != y[0] ? x[0] < y[0] : x[1] < y[1];
				});
			int N = a.size();
			if (N == 1) {
				for (auto [x, y] : qs[u]) {
					ans[y] = x * a[0][0] + a[0][1];
				}
				continue;
			}
			vector<pair<int, ll>> que1(N + 2);
			vector<pair<int, ll>> que2(N + 2);
			int ed1 = 0, ed2 = 0;
			for (int i = 0; i < N; ++i) {
				while (ed1 > 0) {
					ll v1 = a[i][0] * que1[ed1 - 1].second + a[i][1];
					ll v2 = a[que1[ed1 - 1].first][0] * que1[ed1 - 1].second + a[que1[ed1 - 1].first][1];
					if (v1 >= v2) ed1--;
					else break;
				}
				if (ed1 == 0) que1[ed1++] = { i, 1 };
				else {
					ll k1 = a[que1[ed1 - 1].first][0];
					ll b1 = a[que1[ed1 - 1].first][1];
					ll k2 = a[i][0];
					ll b2 = a[i][1];

					ll x0 = ceil(b1 - b2, k2 - k1);
					que1[ed1] = { i, x0 };
					++ed1;
				}
			}
			int p = 0;
			for (int i = 0; i < N; ++i) {
				if (p < ed1 && que1[p].first == i) {
					++p;
					continue;
				}
				while (ed2 > 0) {
					ll v1 = a[i][0] * que2[ed2 - 1].second + a[i][1];
					ll v2 = a[que2[ed2 - 1].first][0] * que2[ed2 - 1].second + a[que2[ed2 - 1].first][1];
					if (v1 >= v2) ed2--;
					else break;
				}
				if (ed2 == 0) que2[ed2++] = { i, 1 };
				else {
					ll k1 = a[que2[ed2 - 1].first][0];
					ll b1 = a[que2[ed2 - 1].first][1];
					ll k2 = a[i][0];
					ll b2 = a[i][1];

					ll x0 = ceil(b1 - b2, k2 - k1);
					que2[ed2] = { i, x0 };
					++ed2;
				}
			}
			int p1 = 0, p2 = 0;
			for (auto [x, idx] : qs[u]) {
				while (p1 < ed1 && que1[p1].second <= x) ++p1;
				while (p2 < ed2 && que2[p2].second <= x) ++p2;
				ll val = a[que1[p1 - 1].first][0] * x + a[que1[p1 - 1].first][1];
				ans[idx] = max(ans[idx], val);
				if (p2 > 0) {
					ans[idx] = max(ans[idx], val + a[que2[p2 - 1].first][0] * x + a[que2[p2 - 1].first][1]);
				}
				if (p1 > 1) {
					ans[idx] = max(ans[idx], val + a[que1[p1 - 2].first][0] * x + a[que1[p1 - 2].first][1]);
				}
				if (p1 < ed1) {
					ans[idx] = max(ans[idx], val + a[que1[p1].first][0] * x + a[que1[p1].first][1]);
				}
			}
		}
	}
	ll dia = 0;
	for (int i = 1; i <= n; ++i) {
		dia = max(dia, dp1[i] + dp2[i]);
	}
	for (int i = 0; i < m; ++i) {
		ans[i] = max(ans[i], dia);
		cout << ans[i] << '\n';
	}
}


int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	solve();
}