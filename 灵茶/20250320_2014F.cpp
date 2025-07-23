#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;

static constexpr ll inf = 0x3f3f3f3f3f3f3f3f;
static constexpr int maxn = 200005;

int n, c;
int head[maxn], to[maxn * 2], nxt[maxn * 2], tot;
ll dp[maxn][2], arr[maxn];

void addEdge(int u, int v) {
	to[++tot] = v;
	nxt[tot] = head[u];
	head[u] = tot;
}

void dfs(int u, int fa) {
	dp[u][1] = arr[u];
	dp[u][0] = 0;
	for (int i = head[u]; i; i = nxt[i]) {
		int v = to[i];
		if (v != fa) {
			dfs(v, u);
			dp[u][1] += max(dp[v][0], dp[v][1] - 2 * c);
			dp[u][0] += max(dp[v][0], dp[v][1]);
		}
	}
}


void solve() {
	cin >> n >> c;
	for (int i = 1; i <= n; ++i) cin >> arr[i];
	for (int i = 1; i <= n; ++i) head[i] = 0;
	tot = 0;
	for (int i = 1, u, v; i < n; ++i) {
		cin >> u >> v;
		addEdge(u, v);
		addEdge(v, u);
	}
	dfs(1, 0);
	cout << max(dp[1][0], dp[1][1]) << '\n';
}

int main() {
	ios::sync_with_stdio(false); cin.tie(NULL);
	int t;
	cin >> t;
	while (t--) solve();
}
