#include <bits/stdc++.h>
using namespace std;


void solve() {
	int n;
	cin >> n;

	vector<int> a(n + 1), b (n + 1);
	for (int i = 1; i <= n; ++i) cin >> a[i];
	for (int i = 1; i <= n; ++i) cin >> b[i];

	// calculate the times move right
	vector<int> p(n + 1);
	vector<int> cnt(n + 1);
	int ans = 0;
	for (int i = 1; i <= n; ++i) 
		p[b[i]] = i;
	for (int i = 1; i <= n; ++i) {
		int times;
		if (p[a[i]] >= i) times = p[a[i]] - i;
		else times = (n - i) + p[a[i]];
		++cnt[times];
		if (cnt[times] > ans) ans = cnt[times];
	}
	cout << ans << endl;
}


int main() {
	ios::sync_with_stdio(false);
	int T = 1;
	while (T--)
		solve();
}