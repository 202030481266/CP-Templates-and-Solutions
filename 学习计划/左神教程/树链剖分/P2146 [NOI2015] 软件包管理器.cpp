// https://www.luogu.com.cn/problem/P2146
#include <bits/stdc++.h> 
#define ls rt << 1
#define rs rt << 1 | 1
#define mid ((l + r) >> 1)
#define lson ls, l, mid
#define rson rs, mid + 1, r
using namespace std;
typedef long long ll;

const ll maxn = 1e5 + 7, N = 4e5 + 7;
ll n, q, exi[N], sum[N], laz[N]; 
ll head[maxn], cnt, total, tp[maxn];
ll id[maxn], rev[maxn], dep[maxn]; 
ll son[maxn], siz[maxn], fa[maxn];
struct edge {ll v, u, nxt;} e[N];

inline void add(ll u, ll v) {
	e[++cnt].v = v;
	e[cnt].nxt = head[u];
	head[u] = cnt;
}

void dfs1(ll u, ll father) {
	siz[u] = 1;
	for(ll i = head[u]; i; i = e[i].nxt) {
		ll v = e[i].v;
		if(v == father) continue;
		dep[v] = dep[u] + 1;
		fa[v] = u;
		dfs1(v, u);
		siz[u] += siz[v];
		if(siz[v] > siz[son[u]]) {
			son[u] = v;
		}
	}
}
void dfs2(ll u, ll father) {
	tp[u] = father;
	id[u] = ++total;
	rev[total] = u;
	if(!son[u]) return;
	dfs2(son[u], father);
	for(ll i = head[u]; i; i = e[i].nxt) {
		ll v = e[i].v;
		if(v == fa[u] || v == son[u]) continue;
		dfs2(v, v);
	}
}

inline void pushup(ll rt) {
	sum[rt] = sum[ls] + sum[rs];
}
inline void pushdown(ll rt, ll l, ll r) {
	if(!laz[rt]) return;
	// the lazy tag is decide by the last one
	if(laz[rt] == 1) {
		sum[ls] = (mid - l + 1);
		sum[rs] = (r - mid);
	} else if(laz[rt] == -1) {
		sum[ls] = sum[rs] = 0;
	}
	laz[ls] = laz[rs] = laz[rt];
	laz[rt] = 0;
}
void update(ll rt, ll l, ll r, ll L, ll R, ll type) {
	if(L <= l && r <= R) {
		// the sequence is 111111
		if(type == 1) {
			sum[rt] = (r - l + 1);
			laz[rt] = type;
			return;
		}
		// the sequence is 000000
		if(type == -1) {
			sum[rt] = 0;
			laz[rt] = type;
			return;
		}
	}
	pushdown(rt, l, r);
	if(R <= mid) update(lson, L, R, type);
	else if(L > mid) update(rson, L, R, type);
	else {
		update(lson, L, mid, type);
		update(rson, mid + 1, R, type);
	}
	pushup(rt);
}
ll query(ll rt, ll l, ll r, ll L, ll R) {
	if(L <= l && r <= R) {
		return sum[rt];
	}
	pushdown(rt, l, r);
	if(R <= mid) return query(lson, L, R);
	else if(L > mid) return query(rson, L, R);
	else return query(lson, L, mid) + query(rson, mid + 1, R);
}

ll ask(ll u, ll v) {
	ll ans = 0;
	while(tp[u] != tp[v]) {
		if(dep[tp[u]] < dep[tp[v]]) {
			swap(u, v);
		}
		ans += query(1, 1, n, id[tp[u]], id[u]);
		u = fa[tp[u]];
	}
	if(dep[u] > dep[v]) swap(u, v);
	ans += query(1, 1, n, id[u], id[v]);
	return ans;
}
// change the sequence as 1111111
void modify(ll u, ll v) {
	while(tp[u] != tp[v]) {
		if(dep[tp[u]] < dep[tp[v]]) {
			swap(u, v);
		}
		update(1, 1, n, id[tp[u]], id[u], 1);
		u = fa[tp[u]];
	}
	if(dep[u] > dep[v]) swap(u, v);
	update(1, 1, n, id[u], id[v], 1);
}


int main() {
	cin >> n;
	for(int i = 2; i <= n; i++) {
		ll x;
		scanf("%lld", &x);
		add(x + 1, i);
		add(i, x + 1);
	}
	dfs1(1, 0);
	dfs2(1, 1);
	cin >> q;
	char s[20];
	ll op;
	while(q--) {
		scanf("%s", s);
		scanf("%lld", &op);
		op++;
		if(s[0] == 'i') {
			ll ans = ask(1, op);
			printf("%lld\n", dep[op] - ans + 1);
			modify(1, op);
		} else {
			ll L = id[op];
			ll R = L + siz[op] - 1;
			ll res = query(1, 1, n, L, R);
			printf("%lld\n", res);
			update(1, 1, n, L, R, -1);
		}
	}
}