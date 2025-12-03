#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;

static constexpr int inf = 0x3f3f3f3f;
static constexpr int maxn = 1000003;

int n, m, V;
int pre[maxn], a[maxn], b[maxn], pos[maxn];
int sum[maxn], ans[maxn];
array<int, 3> qs[maxn];

int fenwick[maxn];

int lowbit(int i) {
	return i & -i;
}

void update(int p, int val) {
	while (p <= n) {
		fenwick[p] ^= val;
		p += lowbit(p);
	}
}

int query(int p) {
	int res = 0;
	while (p > 0) {
		res ^= fenwick[p];
		p -= lowbit(p);
	}
	return res;
}

int main() {
	ios::sync_with_stdio(false); cin.tie(nullptr);
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
		b[i] = a[i];
		sum[i] = sum[i - 1] ^ a[i];
	}
	cin >> m;
	for (int i = 1; i <= m; ++i) {
		cin >> qs[i][0] >> qs[i][1];
		qs[i][2] = i;
	}
	sort(qs + 1, qs + 1 + m, [&](const auto& x, const auto& y) {
		return x[1] != y[1] ? x[1] < y[1] : x[0] < y[0];
		});
	sort(b + 1, b + n + 1);
	V = unique(b + 1, b + n + 1) - b - 1;
	for (int i = 1; i <= n; ++i) {
		int p = lower_bound(b + 1, b + V + 1, a[i]) - b;
		pre[i] = pos[p];
		pos[p] = i;
	}
	int cur = 0, r = 1;
	for (int i = 1; i <= m; ++i) {
		while (r <= qs[i][1]) {
			if (pre[r]) update(pre[r], a[pre[r]]);
			update(r, a[r]);
			++r;
		}
		ans[qs[i][2]] = query(qs[i][1]) ^ query(qs[i][0] - 1) ^ sum[qs[i][1]] ^ sum[qs[i][0] - 1];
	}
	for (int i = 1; i <= m; ++i) cout << ans[i] << '\n';
}