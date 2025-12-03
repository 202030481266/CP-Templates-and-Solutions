#include <bits/stdc++.h>

using namespace std;
using uint = unsigned int;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;

static constexpr int maxn = 100005;
static constexpr int inf = 0x3f3f3f3f;
static constexpr ll llinf = 0x3f3f3f3f3f3f3f3f;
static constexpr int mod = 998244353;

int head[maxn], to[maxn << 1], nxt[maxn << 1], cnt = 0;

void addEdge(int u, int v) {
	to[++cnt] = v;
	nxt[cnt] = head[u];
	head[u] = cnt;
}

int n;
ull C[maxn], dp[maxn], val[maxn], sum[maxn], tot;

void dfs(int u, int fa) {
	sum[u] = C[u];
	for (int i = head[u]; i; i = nxt[i]) {
		if (to[i] != fa) {
			dfs(to[i], u);
			sum[u] += sum[to[i]];
			val[u] += val[to[i]] + sum[to[i]];
		}
	}
}

void cal(int u, int fa) {
	for (int i = head[u]; i; i = nxt[i]) {
		if (to[i] != fa) {
			dp[to[i]] = dp[u] + tot - 2 * sum[to[i]];
			cal(to[i], u);
		}
	}
}

int main() {
	ios::sync_with_stdio(false); cin.tie(nullptr);
	cin >> n;
	for (int i = 1, u, v; i < n; ++i) {
		cin >> u >> v;
		addEdge(u, v);
		addEdge(v, u);
	}
	for (int i = 1; i <= n; ++i) {
		cin >> C[i];
		tot += C[i];
	}
	dfs(1, 0);
	dp[1] = val[1];
	cal(1, 0);
	ull ans = dp[1];
	for (int i = 2; i <= n; ++i) ans = min(ans, dp[i]);
	cout << ans << endl;
}