#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;

static constexpr int inf = 0x3f3f3f3f;
static constexpr int maxn = 200005;

int n, m, a[maxn], b[maxn];
int pre[maxn], suf[maxn];

void solve() {
	cin >> n >> m;
	for (int i = 1; i <= n; ++i) cin >> a[i];
	for (int i = 1; i <= m; ++i) cin >> b[i];
	for (int i = 1; i <= m; ++i) pre[i] = suf[i] = 0;
	int p = 1;
	for (int i = 1; i <= n && p <= m; ++i) {
		if (b[p] <= a[i]) {
			pre[p] = i;
			++p;
		}
	}
	p = m;
	for (int i = n; i >= 1 && p >= 1; --i) {
		if (b[p] <= a[i]) {
			suf[p] = i;
			--p;
		}
	}
	if (pre[m] && pre[m] <= n) {
		cout << 0 << '\n';
		return;
	}
	if (m == 1) {
		cout << b[1] << '\n';
		return;
	}
	int ans = inf;
	for (int i = 1; i <= m; ++i) {
		if (i == 1) {
			if (suf[i + 1]) ans = min(ans, b[i]);
		}
		else if (i == m) {
			if (pre[i - 1]) ans = min(ans, b[i]);
		}
		else {
			if (suf[i + 1] && pre[i - 1] && suf[i + 1] > pre[i - 1]) {
				ans = min(ans, b[i]);
			}
		}
	}
	if (ans == inf) cout << -1 << '\n';
	else cout << ans << '\n';
}

int main() {
	ios::sync_with_stdio(false); cin.tie(nullptr);
	int t;
	cin >> t;
	while (t--) solve();
}