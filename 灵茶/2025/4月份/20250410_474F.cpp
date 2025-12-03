#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;

static constexpr int maxn = 100005;

#define ls rt<<1
#define rs rt<<1|1
#define mid ((l+r)>>1)
#define lson ls, l, mid
#define rson rs, mid + 1, r

int g[maxn << 2], cnt[maxn << 2], a[maxn];


void build(int rt, int l, int r) {
	if (l == r) {
		g[rt] = a[l];
		cnt[rt] = 1;
		return;
	}
	build(lson);
	build(rson);
	g[rt] = gcd(g[ls], g[rs]);
	cnt[rt] = (g[rt] == g[ls] ? cnt[ls] : 0) + (g[rt] == g[rs] ? cnt[rs] : 0);
}

pii query(int rt, int l, int r, int L, int R) {
	if (L <= l && r <= R) {
		return { g[rt], cnt[rt] };
	}
	if (R <= mid) return query(lson, L, R);
	else if (L > mid) return query(rson, L, R);
	else {
		auto [lg, lc] = query(lson, L, mid);
		auto [rg, rc] = query(rson, mid + 1, R);
		int gg = gcd(lg, rg);
		int c = (lg == gg ? lc : 0) + (rg == gg ? rc : 0);
		return { gg, c };
	}
}


int main() {
	ios::sync_with_stdio(false); cin.tie(nullptr);
	int n;
	cin >> n;
	for (int i = 1; i <= n; ++i) cin >> a[i];
	build(1, 1, n);
	int m;
	cin >> m;
	for (int i = 1, l, r; i <= m; ++i) {
		cin >> l >> r;
		auto [_, c] = query(1, 1, n, l, r);
		cout << (r - l + 1 - c) << '\n';
	}
}