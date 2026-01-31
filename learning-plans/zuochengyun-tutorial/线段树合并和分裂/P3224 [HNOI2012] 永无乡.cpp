#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <vector>
using namespace std;
typedef long long ll;
const int maxn = 1e5 + 7, inf = 0x3f3f3f3f, mxr = 1e5 + 7;
int n, m, fa[maxn], q, val[maxn], rk[maxn * 2], cnt = 0;
bool vis[maxn];

#define maxm maxn * 60
#define mid ((l + r)>>1)
int sl[maxm], sr[maxm], sum[maxm], root[maxn];
inline void pushup(int x) {
	sum[x] = sum[sl[x]] + sum[sr[x]];
}
void modify(int& x, int l, int r, int pos, int val) {
	if (x == 0) x = ++cnt;
	if (l == r) {
		sum[x] += val;
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
		return a;
	}
	sl[a] = merge(sl[a], sl[b], l, mid);
	sr[a] = merge(sr[a], sr[b], mid + 1, r);
	pushup(a);
	return a;
}
int query(int x, int l, int r, int k) {
	if (l == r) return l;
	if (sum[sl[x]] >= k) return query(sl[x], l, mid, k);
	else return query(sr[x], mid + 1, r, k - sum[sl[x]]);
}
inline int find(int x) {return x == fa[x] ? x : fa[x] = find(fa[x]);}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= n; i++) fa[i] = i;
	for (int i = 1; i <= n; i++) {
		//int temp; cin >> temp;
		cin >> val[i];
		rk[val[i]] = i;
		root[i] = i;
		cnt++;
	}
	for (int i = 1; i <= n; i++) {
		modify(root[i], 1, mxr, val[i], 1);
	}
	for (int i = 1; i <= m; i++) {
		int u, v;
		cin >> u >> v;
		int fu = find(u), fv = find(v);
		if(fu != fv) {
			fa[fu] = fv;
			root[fv] = merge(root[fv], root[fu], 1, mxr);
		}
	}
	cin >> q;
	for (int i = 1; i <= q; i++) {
		char ch; int x, y;
		cin >> ch >> x >> y;
		if (ch == 'B') {
			int fx = find(x), fy = find(y);
			if (fx == fy) continue;
			fa[fx] = fy;
			root[fy] = merge(root[fy], root[fx], 1, mxr);
		}
		else {
			int fx = find(x);
			int ans = query(root[fx], 1, mxr, y);
			if (y <= 0 || x > n || ans == mxr) {
				cout << -1 << endl;
			} else {
				cout << rk[ans] << endl;
			}
		}
	}
	return 0;
}