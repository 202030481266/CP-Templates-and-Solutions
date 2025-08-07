#include <bits/stdc++.h>

using namespace std;
using uint = unsigned int;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;

static constexpr int maxn = 500005;
static constexpr int inf = 0x3f3f3f3f;
static constexpr ll llinf = 0x3f3f3f3f3f3f3f3f;
static constexpr int mod = 1e9 + 7;

int a[maxn], f[maxn];
int ans[maxn], cnt[maxn];
vector<int> g[maxn];

void dfs(int u, int fa) {
	f[u] = fa;
	for (int v : g[u]) {
		if (v != fa) {
			dfs(v, u);
		}
	}
	for (int v : g[u]) {
		++cnt[a[v]];
		if (cnt[a[v]] > 1) ans[a[v]] = 1;
	}
	for (int v : g[u]) cnt[a[v]] = 0;
} 

void solve() {
	int n;
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
		ans[i] = 0;
		g[i].clear();
	}
	for (int i = 1, u, v; i < n; ++i) {
		cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
		if (a[u] == a[v]) ans[a[u]] = 1;
	}
	dfs(1, 0);
	for (int i = 2; i <= n; ++i) {
		if (f[i] && f[f[i]]) {
			if (a[i] == a[f[f[i]]]) ans[a[i]] = 1;
		}
	}
	for (int i = 1; i <= n; ++i) cout << ans[i];
	cout << '\n';
}

int main() {
	ios::sync_with_stdio(false); cin.tie(nullptr);
	int t;
	cin >> t;
	while (t--) solve();
}