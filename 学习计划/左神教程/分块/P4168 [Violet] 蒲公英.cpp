#include <bits/stdc++.h>
using namespace std;

const int maxn = 40010;
int n, m, lastans, st[300], ed[300], a[maxn], b[maxn];
int f[300][300], cnt[maxn], belong[maxn], g[300][300];

vector<int> p[maxn];

int get(int l, int r, int x) {
	// [L, R)
	auto L = lower_bound(p[x].begin(), p[x].end(), l);
	auto R = upper_bound(p[x].begin(), p[x].end(), r);
	return R - L;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cin >> n >> m;
	for (int i = 1; i <= n; ++i) cin >> a[i];
	for (int i = 1; i <= n; ++i) b[i] = a[i];
	sort(b + 1, b + n + 1);
	int tot = unique(b + 1, b + n + 1) - b - 1;
	for (int i = 1; i <= n; ++i) a[i] = lower_bound(b + 1, b + tot + 1, a[i]) - b;
	for (int i = 1; i <= n; ++i) p[a[i]].emplace_back(i);
	for (int i = 1; i < maxn; ++i) p[i].emplace_back(0x3f3f3f3f);
	int num = sqrt(n);
	for (int i = 1; i <= num; ++i)
		st[i] = n / num * (i - 1) + 1, ed[i] = n / num * i;
	ed[num] = n;
	for (int i = 1; i <= num; ++i) {
		memset(cnt, 0, sizeof(cnt));
		for (int j = st[i]; j <= ed[i]; ++j) belong[j] = i;
		for (int j = i; j <= num; ++j) {
			int& rs = f[i][j];
			int& as = g[i][j];
			rs = f[i][j - 1];
			as = g[i][j - 1];
			for (int k = st[j]; k <= ed[j]; ++k) {
				++cnt[a[k]];
				if (cnt[a[k]] > rs || (cnt[a[k]] == rs && a[k] < as)) {
					as = a[k];
					rs = cnt[a[k]];
				}
			}
		}
	}
	memset(cnt, 0, sizeof(cnt));
	int l, r, all = 0;
	while (m--) {
		cin >> l >> r;
		l = (l + b[lastans] - 1) % n + 1;
		r = (r + b[lastans] - 1) % n + 1;
		if (l > r) swap(l, r);
		all = 0;
		int x = belong[l], y = belong[r];
		if (x == y) {
			for (int i = l; i <= r; ++i) {
				++cnt[a[i]];
				if (cnt[a[i]] > all || (all == cnt[a[i]] && lastans > a[i])) {
					all = cnt[a[i]];
					lastans = a[i];
				}
			}
			for (int i = l; i <= r; ++i) cnt[a[i]] = 0;
		}
		else {
			lastans = g[x + 1][y - 1], all = f[x + 1][y - 1];
			all = get(l, r, lastans);
			for (int i = l; i <= ed[x]; ++i) {
				int k = get(l, r, a[i]);
				if (k > all || (k == all && a[i] < lastans)) {
					all = k;
					lastans = a[i];
				}
			}
			for (int i = r; i >= st[y]; --i) {
				int k = get(l, r, a[i]);
				if (k > all || (k == all && a[i] < lastans)) {
					all = k;
					lastans = a[i];
				}
			}
		}
		cout << b[lastans] << '\n';
	}
}