// https://codeforces.com/problemset/problem/176/E
#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;

static constexpr int maxn = 100005;

int n, m, tot = 0;
int f[maxn][17], dep[maxn], dfn[maxn], ids[maxn];
int head[maxn], nxt[maxn << 1], weight[maxn << 1], to[maxn << 1], ecnt = 0;
ll val[maxn];

void addEdge(int u, int v, int w) {
	to[ecnt] = v;
	weight[ecnt] = w;
	nxt[ecnt] = head[u];
	head[u] = ecnt++;
}

void dfs(int u, int fa, ll value) {
	f[u][0] = fa;
	val[u] = value;
	dep[u] = dep[fa] + 1;
	dfn[u] = ++tot;
	ids[tot] = u;
	for (int i = 1; i < 17; ++i) {
		f[u][i] = f[f[u][i - 1]][i - 1];
	}
	for (int i = head[u]; ~i; i = nxt[i]) {
		int v = to[i], w = weight[i];
		if (v != fa) {
			dfs(v, u, value + w);
		}
	}
}

int lca(int x, int y) {
	if (dep[x] < dep[y]) swap(x, y);
	for (int i = 16; i >= 0; --i) {
		if (dep[f[x][i]] >= dep[y]) {
			x = f[x][i];
		}
	}
	if (x == y) return x;
	for (int i = 16; i >= 0; --i) {
		if (f[x][i] != f[y][i]) {
			x = f[x][i];
			y = f[y][i];
		}
	}
	return f[x][0];
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> n;
	for (int i = 1; i <= n; ++i) head[i] = -1;
	for (int i = 1, u, v, w; i < n; ++i) {
		cin >> u >> v >> w;
		addEdge(u, v, w);
		addEdge(v, u, w);
	}
	dfs(1, 0, 0);
	cin >> m;
	char op;
	ll ans = 0;
	set<int> s;
	for (int i = 1, x; i <= m; ++i) {
		cin >> op;
		if (op == '?') {
			cout << ans << '\n';
		}
		else {
			cin >> x;
			if (op == '+') {
				if (!s.empty()) {
					if (dfn[x] > *s.rbegin()) {
						int y = ids[*s.rbegin()];
						int ff = lca(x, y);
						if (s.size() == 1) {
							ans += val[x] + val[y] - 2 * val[ff];
						}
						else {
							int z = ids[*s.begin()];
							int fff = lca(y, z);
							if (dep[fff] <= dep[ff]) ans += val[x] - val[ff];
							else ans += val[x] + val[fff] - 2 * val[ff];
						}
					}
					else if (dfn[x] < *s.begin()) {
						int y = ids[*s.begin()];
						int ff = lca(x, y);
						if (s.size() == 1) {
							ans += val[x] + val[y] - 2 * val[ff];
						}
						else {
							int z = ids[*s.rbegin()];
							int fff = lca(y, z);
							if (dep[fff] <= dep[ff]) {
								if (ff != x) ans += val[x] - val[ff];
							}
							else ans += val[x] + val[fff] - 2 * val[ff];
						}
					}
					else {
						auto it = s.lower_bound(dfn[x]);
						int f1 = lca(ids[*it], x);
						int f2 = lca(ids[*prev(it)], x);
						int ff = (dep[f1] > dep[f2] ? f1 : f2);
						ans += val[x] - val[ff];
					}
				}
				s.insert(dfn[x]);
			}
			else {
				if (s.size() > 1) {
					if (dfn[x] == *s.rbegin()) {
						int y = ids[*next(s.rbegin())];
						int ff = lca(x, y);
						if (s.size() == 2) {
							ans -= val[x] + val[y] - val[ff] * 2;
						}
						else {
							int z = ids[*s.begin()];
							int fff = lca(z, y);
							if (dep[fff] <= dep[ff]) ans -= val[x] - val[ff];
							else ans -= val[x] + val[fff] - 2 * val[ff];
						}
					}
					else if (dfn[x] == *s.begin()) {
						int y = ids[*next(s.begin())];
						int ff = lca(x, y);
						if (s.size() == 2) {
							ans -= val[x] + val[y] - 2 * val[ff];
						}
						else {
							int z = ids[*s.rbegin()];
							int fff = lca(z, y);

							if (dep[fff] <= dep[ff]) {
								if (ff != x) ans -= val[x] - val[ff];
							}
							else ans -= val[x] + val[fff] - 2 * val[ff];
						}
					}
					else {
						auto it = s.lower_bound(dfn[x]);
						int f1 = lca(ids[*prev(it)], x);
						int f2 = lca(ids[*next(it)], x);
						int ff = (dep[f1] > dep[f2] ? f1 : f2);
						ans -= val[x] - val[ff];
					}
				}
				s.erase(dfn[x]);
			}
		}
	}
}
