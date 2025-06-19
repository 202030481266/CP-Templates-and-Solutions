// https://atcoder.jp/contests/abc332/tasks/abc332_f
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

static constexpr int maxn = 200005;
static constexpr int mod = 998244353;

int n, m;
ll inv[maxn], a[maxn];
ll lazyMul[maxn << 2], lazyAdd[maxn << 2];
ll mul[maxn << 2], add[maxn << 2];

#define ls rt<<1
#define rs rt<<1|1
#define mid ((l+r)>>1)
#define lson ls, l, mid
#define rson rs, mid + 1, r

void applyMul(int rt, ll w) {
	lazyMul[rt] = lazyMul[rt] * w % mod;
	lazyAdd[rt] = lazyAdd[rt] * w % mod;
	mul[rt] = mul[rt] * w % mod;
	add[rt] = add[rt] * w % mod;
}

void applyAdd(int rt, ll w) {
	lazyAdd[rt] = (lazyAdd[rt] + w) % mod;
	add[rt] = (add[rt] + w) % mod;
}

void pushdown(int rt) {
	if (lazyMul[rt] != 1) {
		applyMul(ls, lazyMul[rt]);
		applyMul(rs, lazyMul[rt]);
		lazyMul[rt] = 1;
	}
	if (lazyAdd[rt] != 0) {
		applyAdd(ls, lazyAdd[rt]);
		applyAdd(rs, lazyAdd[rt]);
		lazyAdd[rt] = 0;
	}
}

void update(int rt, int l, int r, int L, int R, int prob, int value) {
	if (L <= l && r <= R) {
		applyMul(rt, (prob - 1) * inv[prob] % mod);
		applyAdd(rt, value * inv[prob] % mod);
		return;
	}
	pushdown(rt);
	if (R <= mid) update(lson, L, R, prob, value);
	else if (L > mid) update(rson, L, R, prob, value);
	else {
		update(lson, L, mid, prob, value);
		update(rson, mid + 1, R, prob, value);
	}
}

void build(int rt, int l, int r) {
	lazyMul[rt] = 1;
	mul[rt] = 1;
	if (l == r) {
		return;
	}
	build(lson);
	build(rson);
}

void dfs(int rt, int l, int r) {
	if (l == r) {
		cout << (a[l] * mul[rt] % mod + add[rt]) % mod << ' ';
		return;
	}
	pushdown(rt);
	dfs(lson);
	dfs(rson);
}

void solve() {
	cin >> n >> m;
	for (int i = 1; i <= n; ++i) cin >> a[i];
	inv[1] = 1;
	for (int i = 2; i <= n; ++i) {
		inv[i] = (ll)(mod - mod / i) * inv[mod % i] % mod;
	}
	build(1, 1, n);
	for (int i = 1, L, R, value; i <= m; ++i) {
		cin >> L >> R >> value;
		update(1, 1, n, L, R, R - L + 1, value);
	}
	dfs(1, 1, n);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	solve();
}