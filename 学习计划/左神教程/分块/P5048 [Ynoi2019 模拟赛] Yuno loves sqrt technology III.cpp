#include <bits/stdc++.h>
using namespace std;

const int maxn = 500010;
int n, m, lastans, st[1000], ed[1000], pos[maxn], a[maxn], b[maxn];
int f[1000][1000], cnt[maxn], belong[maxn];

vector<int> p[maxn];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cin >> n >> m;
	for (int i = 1; i <= n; ++i) cin >> a[i];
	for (int i = 1; i <= n; ++i) b[i] = a[i];
	sort(b + 1, b + n + 1);
	int tot = unique(b + 1, b + n + 1) - b - 1;
	for (int i = 1; i <= n; ++i) a[i] = lower_bound(b + 1, b + tot + 1, a[i]) - b;
	for (int i = 1; i <= n; ++i) {
		p[a[i]].push_back(i);
		pos[i] = p[a[i]].size() - 1;
	}
	int num = sqrt(n);
	for (int i = 1; i <= num; ++i)
		st[i] = n / num * (i - 1) + 1, ed[i] = n / num * i;
	ed[num] = n;
	for (int i = 1; i <= num; ++i) {
		memset(cnt, 0, sizeof(cnt));
		for (int j = st[i]; j <= ed[i]; ++j) belong[j] = i;
		for (int j = i; j <= num; ++j) {
			int& rs = f[i][j];
			rs = f[i][j - 1];
			for (int k = st[j]; k <= ed[j]; ++k)
				rs = max(rs, ++cnt[a[k]]);
		}
	}
	memset(cnt, 0, sizeof(cnt));
	int l, r;
	while (m--) {
		cin >> l >> r;
		l ^= lastans;
		r ^= lastans;
		lastans = 0;
		int x = belong[l], y = belong[r];
		if (x == y) {
			for (int i = l; i <= r; ++i) lastans = max(lastans, ++cnt[a[i]]);
			for (int i = l; i <= r; ++i) cnt[a[i]] = 0;
		}
		else {
			lastans = f[x + 1][y - 1];
			for (int i = l; i <= ed[x]; ++i) {
				int tmp = pos[i];
				while (tmp + lastans < p[a[i]].size() && p[a[i]][tmp + lastans] <= r) ++lastans;
			}
			for (int i = r; i >= st[y]; --i) {
				int tmp = pos[i];
				while (tmp - lastans >= 0 && p[a[i]][tmp - lastans] >= l) ++lastans;
			}
		}
		cout << lastans << '\n';
	}
}