#include <bits/stdc++.h>

using namespace std;
using ll = long long;

static constexpr int maxn = 500005;

int arr[maxn], bl[maxn], br[maxn], b[maxn];
int n, m, a[maxn];

void update(int pos, int val) {
	int l = bl[b[pos]], r = br[b[pos]];
	arr[pos] = val;
	for (int i = l; i <= r; ++i) a[i] = arr[i];
	sort(a + l, a + r + 1);
}

int query(int L, int R, int k) {
	int ans = 0;
	if (b[L] == b[R]) {
		for (int i = L; i <= R; ++i) {
			if (arr[i] >= k) ++ans;
		}
		return ans;
	}
	for (int i = L; i <= br[b[L]]; ++i) {
		if (arr[i] >= k) ++ans;
	}
	for (int i = bl[b[R]]; i <= R; ++i) {
		if (arr[i] >= k) ++ans;
	}
	for (int i = b[L] + 1; i < b[R]; ++i) {
		int pos = lower_bound(a + bl[i], a + br[i] + 1, k) - a;
		ans += br[i] - pos + 1;
	}
	return ans;
}

int main() {
	ios::sync_with_stdio(false); cin.tie(nullptr);
	cin >> n;
	for (int i = 1; i <= n; ++i) cin >> arr[i];
	for (int i = 1; i <= n; ++i) a[i] = arr[i];
	int blen = (int)sqrt(n);
	int bnum = (n + blen - 1) / blen;
	for (int i = 1; i <= n; ++i) {
		b[i] = (i - 1) / blen + 1;
	}
	for (int i = 1; i <= bnum; ++i) {
		bl[i] = (i - 1) * blen + 1;
		br[i] = min(n, i * blen);
		sort(a + bl[i], a + br[i] + 1);
	}
	cin >> m;
	for (int i = 0, op, l, r, pos, k; i < m; ++i) {
		cin >> op;
		if (op) {
			cin >> pos >> k;
			update(pos, k);
		}
		else {
			cin >> l >> r >> k;
			cout << query(l, r, k) << '\n';
		}
	}
}