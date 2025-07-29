#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;

static constexpr int maxn = 5001;
static constexpr int inf = 0x3f3f3f3f;
static constexpr ll llinf = 0x3f3f3f3f3f3f3f3f;
static constexpr int mod = 1e9 + 7;

vector<int> g[maxn];
int n, sz[maxn], a[maxn], ans;
bitset<5001> dp;

void dfs(int u, int fa) {
	sz[u] = 1;
	vector<int> b;
	for (int v : g[u]) {
		if (v != fa) {
			dfs(v, u);
			sz[u] += sz[v];
			b.push_back(sz[v]);
		}
	}
	if (n - sz[u] > 0) b.push_back(n - sz[u]);
	dp.reset();
	dp.set(0);
	for (int v : b) {
		dp |= (dp << v);
	}
	for (int i = 1; i < n - 1; ++i) {
		if (dp.test(i)) a[i] = 1;
	}
}

int main() {
	ios::sync_with_stdio(false); cin.tie(nullptr);
	cin >> n;
	for (int i = 1, u, v; i < n; ++i) {
		cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	dfs(1, 0);
	for (int i = 1; i < n - 1; ++i) {
		ans += a[i];
	}
	cout << ans << '\n';
	for (int i = 1; i < n - 1; ++i) {
		if (a[i]) {
			cout << i << ' ' << n - 1 - i << '\n';
		}
	}
}