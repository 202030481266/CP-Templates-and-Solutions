// https://codeforces.com/contest/600/problem/E
#include <bits/stdc++.h>
using namespace std;

const int N = 100005;
int n, L[N], R[N], num[N], dfn[N], tot = 0;
int sz[N], son[N], col[N];
long long cnt = 0, ans = 0;

vector<int> g[N];
long long f[N];

void dfs0(int u, int fa) {
	L[u] = ++tot;
	dfn[tot] = u;
	sz[u] = 1;
	for (int v : g[u]) {
		if (v != fa) {
			dfs0(v, u);
			sz[u] += sz[v];
			if (!son[u] || sz[v] > sz[son[u]]) son[u] = v;
		}
	}
	R[u] = tot;
}

void dfs1(int u, int fa, bool keep) {
	for (int v : g[u]) {
		if (v == fa || v == son[u]) continue;
		dfs1(v, u, false);
	}
	if (son[u]) dfs1(son[u], u, true);
	for (int v : g[u]) {
		if (v == fa || v == son[u]) continue;
		for (int i = L[v]; i <= R[v]; ++i) {
			int node = dfn[i];
			++num[col[node]];
			if (num[col[node]] > cnt) cnt = num[col[node]], ans = col[node];
			else if (num[col[node]] == cnt) ans += col[node];
		}
	}
	num[col[u]]++;
	if (num[col[u]] > cnt) cnt = num[col[u]], ans = col[u];
	else if (num[col[u]] == cnt) ans += col[u];
	f[u] = ans;
	if (!keep) {
		for (int i = L[u]; i <= R[u]; ++i) --num[col[dfn[i]]];
		cnt = ans = 0;
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cin >> n;
	for (int i = 1; i <= n; ++i) cin >> col[i];
	for (int i = 1; i < n; ++i) {
		int u, v;
		cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	dfs0(1, 0);
	dfs1(1, 0, false);
	for (int i = 1; i <= n; ++i) cout << f[i] << ' ';
	return 0;
}