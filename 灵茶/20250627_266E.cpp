#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int n, m;

#define ls rt<<1
#define rs rt<<1|1
#define mid ((l+r)>>1)
#define lson ls, l, mid
#define rson rs, mid + 1, r

static constexpr int mod = 1e9 + 7;
static constexpr int maxn = 100005;

// 线段树 + 展开式

ll pw[maxn][6];
ll pws[maxn][6];
ll coe[6][6] = {
	{1, 0, 0, 0, 0, 0},
	{1, 1, 0, 0, 0, 0},
	{1, 2, 1, 0, 0, 0},
	{1, 3, 3, 1, 0, 0},
	{1, 4, 6, 4, 1, 0},
	{1, 5, 10, 10, 5, 1}
};

ll sum[maxn << 2][6];
ll lazy[maxn << 2];
ll arr[maxn];

void pushup(int rt, int l, int r) {
	for (int i = 0; i < 6; ++i) {
		sum[rt][i] = sum[ls][i];
		ll tmp = 0, n = (mid - l + 1);
		for (int j = 0; j <= i; ++j) {
			tmp = (tmp + pw[n][i - j] * sum[rs][j] % mod * coe[i][j] % mod) % mod;
		}
		sum[rt][i] = (sum[rt][i] + tmp) % mod;
	}
}

void pushdown(int rt, int l, int r) {
	if (lazy[rt] > -1) {
		lazy[ls] = lazy[rs] = lazy[rt];
		for (int i = 0; i < 6; ++i) {
			sum[ls][i] = pws[mid - l + 1][i] * lazy[rt] % mod;
			sum[rs][i] = pws[r - mid][i] * lazy[rt] % mod;
		}
		lazy[rt] = -1;
	}
}

void build(int rt, int l, int r) {
	lazy[rt] = -1;
	if (l == r) {
		for (int i = 0; i < 6; ++i) sum[rt][i] = arr[l];
		return;
	}
	build(lson);
	build(rson);
	pushup(rt, l, r);
}

void update(int rt, int l, int r, int L, int R, int val) {
	if (L <= l && r <= R) {
		lazy[rt] = val;
		for (int i = 0; i < 6; ++i) sum[rt][i] = val * pws[r - l + 1][i] % mod;
		return;
	}
	pushdown(rt, l, r);
	if (R <= mid) update(lson, L, R, val);
	else if (L > mid) update(rson, L, R, val);
	else {
		update(lson, L, mid, val);
		update(rson, mid + 1, R, val);
	}
	pushup(rt, l, r);
}

ll query(int rt, int l, int r, int L, int R, int k, int offset) {
	if (L <= l && r <= R) {
		ll res = 0;
		for (int i = 0; i <= k; ++i) {
			res = (res + pw[offset][k - i] * sum[rt][i] % mod * coe[k][i] % mod) % mod;
		}
		return res;
	}
	pushdown(rt, l, r);
	if (R <= mid) return query(lson, L, R, k, offset);
	else if (L > mid) return query(rson, L, R, k, offset);
	else {
		ll lans = query(lson, L, mid, k, offset);
		ll rans = query(rson, mid + 1, R, k, offset + mid - L + 1);
		return (lans + rans) % mod;
	}
}

int main() {
	ios::sync_with_stdio(false); cin.tie(nullptr);
	cin >> n >> m;
	for (int i = 1; i <= n; ++i) cin >> arr[i];
	pw[0][0] = 1; // a special value
	for (int i = 1; i <= n; ++i) {
		pw[i][0] = 1;
		for (int j = 1; j < 6; ++j) pw[i][j] = pw[i][j - 1] * i % mod;
	}
	for (int i = 0; i < 6; ++i) {
		pws[1][i] = pw[1][i];
		for (int j = 2; j <= n; ++j) pws[j][i] = (pws[j - 1][i] + pw[j][i]) % mod;
	}
	build(1, 1, n);
	char op;
	for (int i = 0, l, r, x; i < m; ++i) {
		cin >> op >> l >> r >> x;
		if (op == '?') {
			cout << query(1, 1, n, l, r, x, 0) << '\n';
		}
		else {
			update(1, 1, n, l, r, x);
		}
	}
}