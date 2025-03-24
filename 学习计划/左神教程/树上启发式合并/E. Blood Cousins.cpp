// https://codeforces.com/problemset/problem/208/E
#include <iostream> 
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;
const int maxn = 1e5 + 7, inf = 0x3f3f3f3f;
const int maxm = maxn * 60, mxr = maxn;
vector<int> G[maxn];
vector<pair<int,int>> qq[maxn];
int n, m, ans[maxn];
struct Query {int node, p, anc;} q[maxn];

int dep[maxn], fa[maxn][30]; 
void dfs(int u, int father) {
	dep[u] = dep[father] + 1;
	fa[u][0] = father;
	for(int i = 1; (1 << i) <= dep[u]; i++)
		fa[u][i] = fa[fa[u][i - 1]][i - 1];
	for(auto v : G[u]) {
		if(v == father) continue;
		dfs(v, u);
	}
}

#define mid ((l + r) >> 1)
int sum[maxm], sl[maxm], sr[maxm], root[maxn], cnt = 0;
inline void pushup(int x) {
	sum[x] = sum[sl[x]] + sum[sr[x]];
}
void modify(int& x, int l, int r, int pos, int val) {
	if(x == 0) x = ++cnt;
	if(l == r) {
		sum[x] += val;
		return; 
	}
	if(pos <= mid) modify(sl[x], l, mid, pos, val);
	else modify(sr[x], mid + 1, r, pos, val);
	pushup(x);
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
int query(int x, int l, int r, int val) {
	if(x == 0) return 0;
	if(l == r) {
		return sum[x];
	}
	if(val <= mid) return query(sl[x], l, mid, val);
	else return query(sr[x], mid + 1, r, val);
}
void ini(int u) {
	modify(u, 1, mxr, dep[u], 1);
	for(auto v : G[u]) {
		if(v == fa[u][0]) continue;
		ini(v);
		root[u] = merge(root[u], root[v], 1, mxr);
	}
	for(auto p : qq[u]) {
		int id = p.second, num = p.first;
		ans[id] = query(root[u], 1, mxr, dep[u] + num) - 1;
	}
}

int rootc, rot[maxn];
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin >> n;
	for(int i = 1; i <= n; i++) {
		int x;
		cin >> x;
		root[i] = i; cnt++;
		if(x) {
			G[i].push_back(x);
			G[x].push_back(i);
		} else {
			rootc++;
			rot[rootc] = i;
		}
	}
	for(int i = 1; i <= rootc; i++) {
		dep[rot[i]] = 1; 
		dfs(rot[i], 0);
	}
	int T;
	cin >> T;
	for(int i = 1; i <= T; i++) {
		cin >> q[i].node >> q[i].p;
		int t = dep[q[i].node] - q[i].p, x = q[i].node;
		for(int i = 20; (i + 1); i--)
			if(dep[fa[x][i]] > t) x = fa[x][i];
		q[i].anc = fa[x][0]; 
		qq[q[i].anc].push_back(make_pair(q[i].p, i));
	}
	for(int i = 1; i <= rootc; i++) {
		ini(rot[i]);
	}
	for(int i = 1; i <= T; i++)
		cout << ans[i] << " ";
}