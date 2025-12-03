#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;

static constexpr int inf = 0x3f3f3f3f;
static constexpr int maxn = 305;

int n, dis[maxn][maxn], value[maxn], vis[maxn];
ll dp[maxn][maxn];
char grid[maxn][maxn];
vector<int> g[maxn];


int main() {
	ios::sync_with_stdio(false); cin.tie(NULL);
	cin >> n;
	for (int i = 1; i <= n; ++i) cin >> value[i];
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			cin >> grid[i][j];
			if (grid[i][j] == 'Y') {
				g[i].push_back(j);
			}
		}
	}
	memset(dis, 0x3f, sizeof(dis));
	for (int i = 1; i <= n; ++i) {
		memset(vis, 0, sizeof(vis));
		queue<int> q;
		q.push(i);
		dis[i][i] = 0;
		dp[i][i] = value[i];
		vis[i] = 1;
		while (!q.empty()) {
			int u = q.front();
			q.pop();
			for (int v : g[u]) {
				if (!vis[v]) {
					dis[i][v] = dis[i][u] + 1;
					dp[i][v] = dp[i][u] + value[v];
					vis[v] = 1;
					q.push(v);
				}
				else {
					if (dis[i][v] == dis[i][u] + 1) {
						dp[i][v] = max(dp[i][v], dp[i][u] + value[v]);
					}
				}
			}
		}
	}
	int m;
	cin >> m;
	for (int i = 1, u, v; i <= m; ++i) {
		cin >> u >> v;
		if (dis[u][v] == inf) cout << "Impossible" << '\n';
		else {
			cout << dis[u][v] << ' ' << dp[u][v] << '\n';
		}
	}
}
