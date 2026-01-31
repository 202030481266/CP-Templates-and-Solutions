#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <vector>
using namespace std;
typedef long long ll;
const int maxn = 1e5 + 7, mxr = 1e9;
int n, m;

#define maxm maxn * 50
#define mid ((l+r)>>1)
int sl[maxm], sr[maxm], root[maxm], fa[maxn], siz[maxn];
ll sum[maxm], maxx[maxm], ans[maxn], val[maxn], cnt = 0;

vector<int> G[maxn];

inline void pushup(int x) {
	sum[x] = sum[sl[x]] + sum[sr[x]];
}
void modify(int& x, int l, int r, int pos, int val) {
	if (x == 0) x = ++cnt;
	if (l == r) {
		sum[x] += val;
		maxx[x] = l;
		return;
	}
	if (pos <= mid) modify(sl[x], l, mid, pos, val);
	else modify(sr[x], mid + 1, r, pos, val);
	pushup(x);
}
int merge(int a, int b, int l, int r) {
	if (a == 0 || b == 0) return a + b;
	if (l == r) {
		sum[a] += sum[b];
		maxx[a] = l;
		return a;
	}
	sl[a] = merge(sl[a], sl[b], l, mid);
	sr[a] = merge(sr[a], sr[b], mid + 1, r);
	pushup(a);
	return a;
}
ll query(int x, int l, int r, int L, int R) {
	if (L <= l && r <= R) { return sum[x]; }
	if (L > mid) return query(sr[x], mid + 1, r, L, R);
	else if (R <= mid) return query(sl[x], l, mid, L, R);
	else return query(sl[x], l, mid, L, mid) + query(sr[x], mid + 1, r, mid + 1, R);
}
void dfs(int u, int father) {
	siz[u] = 1;
	for (auto v : G[u]) {
		if (v == father) continue;
		dfs(v, u);
		siz[u] += siz[v];
		root[u] = merge(root[u], root[v], 1, mxr);
	}
	modify(root[u], 1, mxr, val[u], 1);
	ll ret = query(root[u], 1, mxr, val[u] + 1, mxr);
	ans[u] = (siz[u] > 1) ? ret : 0;
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> val[i];
		root[i] = i;
		cnt++;
	}
	for (int i = 2; i <= n; i++) {
		cin >> fa[i];
		G[fa[i]].push_back(i);
		G[i].push_back(fa[i]);
	}
	dfs(1, 0);
	for (int i = 1; i <= n; i++) cout << ans[i] << endl;
}
