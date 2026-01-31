// /usr/liushulin
// -*- coding:UTF-8 -*-
/*#########################################################################
# File Name: luogu_4556.cpp
# Author: xiaoshulin
# Created Time: 2021/12/10 16:49:32
#########################################################################*/
#include <bits/stdc++.h> 
using namespace std;
const int maxn = 1e5 + 7, inf = 0x3f3f3f3f, mxr = 1e5, LOG = 19;
vector<int> G[maxn];
int n, m; 

const int maxm = maxn * 100;
int tree[maxm], sum[maxm], sl[maxm], sr[maxm], cnt = 0;
#define mid ((l + r) >> 1)

inline void pushup(int rt) {
	if(sl[rt] == 0) {
		tree[rt] = tree[sr[rt]];
		sum[rt] = sum[sr[rt]];
		return;
	}
	if(sr[rt] == 0) {
		tree[rt] = tree[sl[rt]];
		sum[rt] = sum[sl[rt]];
		return;
	}
	if(sum[sl[rt]] >= sum[sr[rt]]) {
		sum[rt] = sum[sl[rt]];
		tree[rt] = tree[sl[rt]];
	} else {
		sum[rt] = sum[sr[rt]];
		tree[rt] = tree[sr[rt]];
	}
}
void modify(int &rt, int l, int r, int pos, int val) {
	if(rt == 0) rt = ++cnt;
	if(l == r) {
		sum[rt] += val;
		tree[rt] = pos;
		return;
	}
	if(pos <= mid) modify(sl[rt], l, mid, pos, val);
	else modify(sr[rt], mid + 1, r, pos, val);
	pushup(rt);
}
int merge(int a, int b, int l, int r) {
	if(a == 0 || b == 0) return a + b;
	if(l == r) {
		sum[a] += sum[b];
		return a;
	}
	sl[a] = merge(sl[a], sl[b], l, mid);
	sr[a] = merge(sr[a], sr[b], mid + 1, r);
	pushup(a);
	return a;
}
// lca
int f[maxn][LOG], dep[maxn];
void dfs(int u, int fa) {
	dep[u] = dep[fa] + 1;
	f[u][0] = fa;
	for(int i = 1; i < LOG; i++)
		f[u][i] = f[f[u][i - 1]][i - 1];
	for(auto v : G[u]) {
		if(v != fa) dfs(v, u);
	}
}
inline int lca(int x, int y) {
	if(dep[x] < dep[y]) swap(x, y);
	for(int i = LOG - 1; i >= 0; i--) {
		if(dep[f[x][i]] >= dep[y]) x = f[x][i];
	}
	if(x == y) return x;
	for(int i = LOG - 1; i >= 0; i--) {
		if(f[x][i] != f[y][i]) x = f[x][i], y = f[y][i];
	}
	return f[x][0];
}

int ret[maxn], ans[maxn];
void solve(int u, int fa) {
	for(auto v : G[u]) {
		if(v == fa) continue;
		solve(v, u);
		ret[u] = merge(ret[u], ret[v], 1, mxr);
	}
	ans[u] = tree[ret[u]];
	if(sum[ret[u]] == 0) ans[u] = 0;
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> m;
	for(int i = 1; i < n; i++) {
		int u, v;
		cin >> u >> v;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	dfs(1, 0);
	for(int i = 1; i <= m; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		int anc = lca(a, b);
		modify(ret[a], 1, mxr, c, 1);
		modify(ret[b], 1, mxr, c, 1);
		modify(ret[anc], 1, mxr, c, -1);
		modify(ret[f[anc][0]], 1, mxr, c, -1);
	}
	solve(1, 0);
	for(int i = 1; i <= n; i++) 
		cout << ans[i] << endl;
}