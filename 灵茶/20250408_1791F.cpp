#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

static constexpr int maxn = 200005;

int fenwick[maxn], n, m, a[maxn];

void add(int i, int v) {
	while (i <= n) {
		fenwick[i] += v;
		i += (i & -i);
	}
}

int query(int i) {
	int res = 0;
	while (i > 0) {
		res += fenwick[i];
		i -= (i & -i);
	}
	return res;
}

int to_digit_sum(int val) {
	int res = 0;
	while (val) {
		res += val % 10;
		val /= 10;
	}
	return res;
}

void solve() {
	cin >> n >> m;
	for (int i = 1; i <= n; ++i) cin >> a[i];
	for (int i = 0; i <= n + 1; ++i) fenwick[i] = 0;
	for (int i = 1, op, l, r, x, nxt; i <= m; ++i) {
		cin >> op;
		if (op == 1) {
			cin >> l >> r;
			add(l, 1);
			add(r + 1, -1);
		}
		else {
			cin >> x;
			int k = query(x), t = k;
			while (t--) {
				nxt = to_digit_sum(a[x]);
				if (nxt == a[x]) {
					break;
				}
				a[x] = nxt;
			}
			add(x, -k);
			add(x + 1, k);
			cout << a[x] << '\n';
		}
	}
}


int main() {
	ios::sync_with_stdio(false); cin.tie(nullptr);
	int t;
	cin >> t;
	while (t--) solve();
}