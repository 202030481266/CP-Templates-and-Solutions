#include <bits/stdc++.h>

using namespace std;

static constexpr int inf = 0x3f3f3f3f;

int main() {
	ios::sync_with_stdio(false); cin.tie(nullptr);
	int n;
	cin >> n;
	vector<int> a(n), b(n, inf), c(n);
	for (int& v : a) cin >> v;
	vector dp(n, vector<int>(2, inf));
	int p = -1;
	for (int i = 0; i < n; ++i) {
		if (a[i] != -1) {
			if (p == -1) {
				dp[i][0] = 1;
				c[i] = i - p - 1;
			}
			else {
				int sub = a[i] - a[p], spaces = i - p - 1;
				if (dp[p][0] <= dp[p][1]) {
					dp[i][0] = dp[p][0] + 1;
				}
				else {
					dp[i][0] = dp[p][1] + 1;
					int x = (b[p] >= 0 ? inf : (a[p] - 1) / (-b[p]));
					c[i] = max(0, spaces - x);
				}
				if (sub % (i - p) == 0) {
					b[i] = sub / (i - p);
					if (c[p] > 0) {
						int lim = (a[p] - 1) / c[p];
						dp[i][1] = (b[i] > lim ? dp[p][0] + 1 : dp[p][0]);
					}
					else {
						dp[i][1] = dp[p][0];
					}
					if (b[p] != inf && b[i] == b[p]) {
						dp[i][1] = min(dp[i][1], dp[p][1]);
					}
				}
			}
			p = i;
		}
	}
	if (p == -1) cout << 1 << endl;
	else {
		if (dp[p][0] <= dp[p][1]) cout << dp[p][0] << endl;
		else {
			int x = (b[p] >= 0 ? inf : (a[p] - 1) / (-b[p]));
			if (x >= n - p - 1) cout << dp[p][1] << endl;
			else cout << dp[p][1] + 1 << endl;
		}
	}
}