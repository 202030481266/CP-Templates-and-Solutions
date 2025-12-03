// https://codeforces.com/problemset/problem/498/D
// LCM 构造技巧应用，中国剩余定理构造解的技巧
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

static constexpr int inf = 0x3f3f3f3f;
static constexpr int maxn = 1e5 + 7;
int n, m;

#define ls rt<<1
#define rs rt<<1|1
#define mid ((l+r)>>1)
#define lson ls, l, mid
#define rson rs, mid + 1, r

int a[maxn<<2][60];

void pushup(int rt) {
	for (int j = 0; j < 60; ++j) {
		a[rt][j] = a[ls][j] + a[rs][(j + a[ls][j]) % 60];
	}
}

void update(int rt, int l, int r, int pos, int val) {
	if (l == r) {
		for (int j = 0; j < 60; ++j) {
			a[rt][j] = (j % val == 0 ? 2 : 1);
		}
		return;
	}
	if (pos <= mid) update(lson, pos, val);
	else update(rson, pos, val);
	pushup(rt);
}

int query(int rt, int l, int r, int L, int R, int val) {
	if (L <= l && r <= R) {
		return a[rt][val];
	}
	if (R <= mid) return query(lson, L, R, val);
	else if (L > mid) return query(rson, L, R, val);
	else {
		int l_ans = query(lson, L, mid, val);
		return l_ans + query(rson, mid + 1, R, (val + l_ans) % 60);
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	// L = lcm(2,3,4,5,6)
	// L*k + x is the same as x
	// x -> x+d1 -> x+d1+d2
	// L*k + x -> L*x + (x+d1) -> L*x + (x+d1+d2)
	cin >> n;
	for (int i = 1, x; i <= n; ++i) {
		cin >> x;
		update(1, 1, n, i, x);
	}
	cin >> m;
	char op;
	for (int i = 1, x, y; i <= m; ++i) {
		cin >> op >> x >> y;
		if (op == 'C') {
			update(1, 1, n, x, y);
		}
		else {
			cout << query(1, 1, n, x, y - 1, 0) << '\n';
		}
	}
}