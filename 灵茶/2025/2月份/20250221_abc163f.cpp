#include <bits/stdc++.h>

using namespace std;
using uint = unsigned int;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;

static constexpr int maxn = 200005;
static constexpr int inf = 0x3f3f3f3f;
static constexpr ll llinf = 0x3f3f3f3f3f3f3f3f;
static constexpr int mod = 998244353;

int head[maxn], to[maxn << 1], nxt[maxn << 1], ecnt = 0;
int n, arr[maxn];

int color[maxn];
int cnt[maxn], root[maxn];
int siz[maxn];

void addEdge(int u, int v) {
	to[++ecnt] = v;
	nxt[ecnt] = head[u];
	head[u] = ecnt;
}

ll ans[maxn];

void dfs(int u, int fa) {
	int pre = color[arr[u]];
	siz[u] = 1;
	for (int i = head[u]; i; i = nxt[i]) {
		if (to[i] != fa) {
			color[arr[u]] = to[i];
			dfs(to[i], u);
			siz[u] += siz[to[i]];
		}
	}
	if (u == 1) { // 计算贡献
		for (int i = 1; i <= n; ++i) {
			if (i != arr[1] && root[i] < 0) { // 需要判断颜色
				root[i] += siz[1];
				ans[i] -= 1ll * root[i] * (root[i] + 1) / 2;
			}
		}
	}
	else {
		cnt[u] += siz[u];
		if (arr[u] != arr[fa]) { // 这个确实属于fa下面的颜色的起点的根
			ans[arr[fa]] -= 1ll * cnt[u] * (cnt[u] + 1) / 2;
		}
	}
	if (pre == 1) root[arr[u]] -= siz[u];
	else cnt[pre] -= siz[u];
	color[arr[u]] = pre;
}

int main() {
	ios::sync_with_stdio(false); cin.tie(nullptr);
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		cin >> arr[i];
		if (!color[arr[i]]) {
			color[arr[i]] = 1;
			ans[arr[i]] = 1ll * n * (n + 1) / 2;
		}
	}
	for (int i = 1, u, v; i < n; ++i) {
		cin >> u >> v;
		addEdge(u, v);
		addEdge(v, u);
	}
	dfs(1, 0);
	for (int i = 1; i <= n; ++i) cout << ans[i] << '\n';
}