#include <bits/stdc++.h>
using namespace std;
using ll = long long;

static constexpr int MAXN = 200005;

int n, arr[MAXN], b[MAXN], vis[MAXN];
int head[MAXN], to[MAXN], nxt[MAXN], cnt = 0;

void addEdge(int u, int v) {
	to[++cnt] = v;
	nxt[cnt] = head[u];
	head[u] = cnt;
}

int lowbit(int i) {
	return i & -i;
}

int fenwick[MAXN];

void add(int p, int val) {
	while (p <= n) {
		fenwick[p] += val;
		p += lowbit(p);
	}
}

int query(int p) {
	int res = 0;
	while (p) {
		res += fenwick[p];
		p -= lowbit(p);
	}
	return res;
}

void solve() {
	cin >> n;
	for (int i = 1; i <= n; ++i) cin >> arr[i];
	for (int i = 1; i <= n; ++i) {
		if (arr[i] + 1 <= n) {
			addEdge(arr[i] + 1, i);
		}
		add(i, 1);
	}
	ll ans = 0;
	for (int i = 1; i < n; ++i) {
		for (int x = head[i]; x; x = nxt[x]) {
			int v = to[x];
			if (!vis[v]) {
				add(v, -1);
				vis[v] = 1;
			}
		}
		if (!vis[i]) {
			add(i, -1);
			vis[i] = 1;
		}
		int k = min(n, arr[i]);
		ans += query(k);
	}
	cout << ans << '\n';
}


int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	solve();
}