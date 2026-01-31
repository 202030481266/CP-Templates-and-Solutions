// 启发式合并模板题目
#include <bits/stdc++.h>
using namespace std;
const int N = 200005;
int sz[N], n, big[N], col[N], L[N], R[N], Node[N], totDfn = 0;
int ans[N], cnt[N], totColor = 0;
vector<int> g[N];

void add(int u) {
	if (cnt[col[u]] == 0) ++totColor;
	cnt[col[u]]++;
}
void del(int u) {
	cnt[col[u]]--;
	if (cnt[col[u]] == 0) --totColor;
}
void dfs0(int u, int fa) {
	L[u] = ++totDfn;
	Node[totDfn] = u;
	sz[u] = 1;
	for (int v : g[u]) {
		if (v != fa) {
			dfs0(v, u);
			sz[v] += sz[u];
			if (!big[u] || sz[v] > sz[big[u]]) big[u] = v;
		}
	}
	R[u] = totDfn;
}
void dfs1(int u, int fa, bool keep) {
	for (int v : g[u]) {
		if (v != fa && v != big[u])
			dfs1(v, u, false);
	}
	if (big[u]) dfs1(big[u], u, true);
	for (int v : g[u]) {
		if (v != fa && v != big[u]) {
			for (int i = L[v]; i <= R[v]; ++i) add(Node[i]);
		}
	}
	add(u);
	ans[u] = totColor;
	if (!keep) for (int i = L[u]; i <= R[u]; ++i) del(Node[i]);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cin >> n;
	for (int i = 0; i < n - 1; ++i) {
		int u, v;
		cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	for (int i = 1; i <= n; ++i) cin >> col[i];
	dfs0(1, 0);
	dfs1(1, 0, false);
	int m;
	cin >> m;
	for (int i = 1; i <= m; ++i) {
		int tmp;
		cin >> tmp;
		cout << ans[tmp] << '\n';
	}
	return 0;
}