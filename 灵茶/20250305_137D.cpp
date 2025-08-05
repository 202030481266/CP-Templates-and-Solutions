#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;

static constexpr int maxn = 100005;
static constexpr int inf = 0x3f3f3f3f;
static constexpr ll llinf = 0x3f3f3f3f3f3f3f3f;
static constexpr int mod = 1e9 + 7;



int main() {
	ios::sync_with_stdio(false); cin.tie(nullptr);
	string s;
	cin >> s;
	int n = s.size();
	vector dp(n + 1, vector<int>(n + 1, 0));
	for (int len = 2; len <= n; ++len) {
		for (int i = 1; i + len - 1 <= n; ++i) {
			int j = i + len - 1;
			if (len == 2) dp[i][j] = (s[i - 1] == s[j - 1] ? 0 : 1);
			else dp[i][j] = dp[i + 1][j - 1] + (s[i - 1] == s[j - 1] ? 0 : 1);
		}
	}
	int k;
	cin >> k;
	vector f(n + 1, vector<int>(k + 1, inf));
	vector pre(n + 1, vector<int>(k + 1, 0));
	f[0][0] = 0;
	for (int i = 1; i <= n; ++i) {
		for (int j = i; j >= 1; --j) {
			for (int x = 1; x <= min(k, j); ++x) {
				if (f[j - 1][x - 1] < inf) {
					if (f[j - 1][x - 1] + dp[j][i] < f[i][x]) {
						f[i][x] = f[j - 1][x - 1] + dp[j][i];
						pre[i][x] = j - 1;
					}
				}
			}
		}
	}
	vector<string> ans;
	int mn = 0, cur = n;
	for (int i = 1; i <= k; ++i) {
		if (f[n][i] < f[n][mn]) {
			mn = i;
		}
	}
	cout << f[n][mn] << '\n';
	while (cur) {
		int p = pre[cur][mn];
		ans.push_back(s.substr(p, cur - p));
		cur = p;
		--mn;
	}
	reverse(ans.begin(), ans.end());
	int m = ans.size();
	for (int i = 0; i < m; ++i) {
		int l = 0, r = ans[i].size() - 1;
		while (l < r) {
			if (ans[i][l] != ans[i][r]) ans[i][r] = ans[i][l];
			++l;
			--r;
		}
		if (i == m - 1) cout << ans[i] << '\n';
		else cout << ans[i] << '+';
	}
}