#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;

static constexpr int inf = 0x3f3f3f3f;
static constexpr int maxn = 100005;

// 线段树orFHQ

int n, m, N;
ll arr[maxn], disc[maxn<<1], temp[maxn];
array<int, 3> ops[maxn];

#define ls rt<<1
#define rs rt<<1|1
#define mid ((l+r)>>1)
#define lson ls,l,mid
#define rson rs,mid+1,r

static constexpr int maxv = 200005;

int coe_lazy[maxv << 2], init_coe[maxv], init_val[maxv];
ll mul_sum[maxv << 2], add_sum[maxv << 2];

void pushup(int rt) {
	add_sum[rt] = add_sum[ls] + add_sum[rs];
	mul_sum[rt] = mul_sum[ls] + mul_sum[rs];
}

void pushdown(int rt) {
	if (coe_lazy[rt]) {
		coe_lazy[ls] += coe_lazy[rt];
		coe_lazy[rs] += coe_lazy[rt];
		mul_sum[ls] += coe_lazy[rt] * add_sum[ls];
		mul_sum[rs] += coe_lazy[rt] * add_sum[rs];
		coe_lazy[rt] = 0;
	}
}

void build(int rt, int l, int r) {
	if (l == r) {
		add_sum[rt] = init_val[l];
		coe_lazy[rt] = init_coe[l];
		mul_sum[rt] = init_val[l] * init_coe[l];
		return;
	}
	build(lson);
	build(rson);
	pushup(rt);
}

void modify_val(int rt, int l, int r, int p, int val) {
	if (l == r) {
		add_sum[rt] += val;
		mul_sum[rt] = add_sum[rt] * coe_lazy[rt];
		return;
	}
	pushdown(rt);
	if (p <= mid) modify_val(lson, p, val);
	else modify_val(rson, p, val);
	pushup(rt);
}

void modify_coe(int rt, int l, int r, int L, int R, int c) {
	if (L <= l && r <= R) {
		coe_lazy[rt] += c;
		mul_sum[rt] += c * add_sum[rt];
		return;
	}
	pushdown(rt);
	if (R <= mid) modify_coe(lson, L, R, c);
	else if (L > mid) modify_coe(rson, L, R, c);
	else {
		modify_coe(lson, L, mid, c);
		modify_coe(rson, mid + 1, R, c);
	}
	pushup(rt);
}

ll query(int rt, int l, int r, int L, int R, int t) {
	if (L <= l && r <= R) {
		return t ? mul_sum[rt] : add_sum[rt];
	}
	pushdown(rt);
	if (R <= mid) return query(lson, L, R, t);
	else if (L > mid) return query(rson, L, R, t);
	else return query(lson, L, mid, t) + query(rson, mid + 1, R, t);
}

int fenwick[maxv], vis[maxv];

inline int lowbit(int i) {
	return i & -i;
}

void update(int p, int val) {
	while (p <= N) {
		fenwick[p] += val;
		p += lowbit(p);
	}
}

int getSize (int p) {
	int res = 0;
	while (p > 0) {
		res += fenwick[p];
		p -= lowbit(p);
	}
	return res;
}

int getIdx(ll val) {
	return lower_bound(disc + 1, disc + 1 + N, val) - disc;
}

int main() {
	ios::sync_with_stdio(false); cin.tie(nullptr);
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		cin >> arr[i];
		disc[++N] = arr[i];
		temp[i] = arr[i];
	}
	cin >> m;
	for (int i = 1; i <= m; ++i) {
		cin >> ops[i][0] >> ops[i][1] >> ops[i][2];
		if (ops[i][0] == 1) {
			temp[ops[i][1]] += ops[i][2];
			disc[++N] = temp[ops[i][1]];
		}
	}
	for (int i = 1; i <= n; ++i) temp[i] = arr[i];
	sort(disc + 1, disc + 1 + N);
	sort(temp + 1, temp + 1 + n);
	N = unique(disc + 1, disc + 1 + N) - disc - 1;
	for (int i = 1, j = 1, cnt = 0; i <= N; ++i) {
		if (j <= n && temp[j] == disc[i]) {
			++cnt;
			++j;
			init_val[i] = disc[i];
			update(i, 1);
			vis[i] = 1;
		}
		init_coe[i] = cnt;
	}
	build(1, 1, N);
	for (int i = 1; i <= m; ++i) {
		if (ops[i][0] == 1) {
			if (ops[i][2] > 0) {
				int l = getIdx(arr[ops[i][1]]), r = getIdx(arr[ops[i][1]] + ops[i][2]);
				modify_val(1, 1, N, l, -disc[l]);
				modify_coe(1, 1, N, l, r - 1, -1);
				modify_val(1, 1, N, r, disc[r]);
				update(l, -1);
				update(r, 1);
				vis[l] = 0;
				vis[r] = 1;
			}
			else if (ops[i][2] < 0) {
				int l = getIdx(arr[ops[i][1]] + ops[i][2]), r = getIdx(arr[ops[i][1]]);
				modify_val(1, 1, N, r, -disc[r]);
				modify_coe(1, 1, N, l, r - 1, 1);
				modify_val(1, 1, N, l, disc[l]);
				update(r, -1);
				update(l, 1);
				vis[l] = 1;
				vis[r] = 0;
			}
			arr[ops[i][1]] += ops[i][2];
		}
		else {
			int l = getIdx(ops[i][1]);
			if (l <= N) {
				int r = getIdx(ops[i][2] + 1); // [l, r)
				if (r > l) {
					int sz = getSize(r - 1) - getSize(l - 1);
					if (sz) {
						ll add_s = query(1, 1, N, l, r - 1, 0);
						ll mul_s = query(1, 1, N, l, r - 1, 1);
						int st = (vis[l] ? getSize(l) : getSize(l) + 1);
						int offset = -sz - st * 2 + 1;
						cout << (mul_s * 2 + add_s * offset) << '\n';
					}
					else cout << 0 << '\n';
				}
				else cout << 0 << '\n';
			}
			else cout << 0 << '\n';
		}
	}
}