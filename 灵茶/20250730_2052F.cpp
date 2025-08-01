#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;

static constexpr int maxn = 200005;
static constexpr int inf = 0x3f3f3f3f;
static constexpr ll llinf = 0x3f3f3f3f3f3f3f3f;
static constexpr int mod = 1e9 + 7;


void solve() {
	int n;
	cin >> n;
	vector g(2, vector<char>(n + 1));
	for (int i = 0; i < 2; ++i) {
		for (int j = 1; j <= n; ++j) {
			cin >> g[i][j];
		}
	}
	vector dp(n + 1, vector<int>(3, 0));
	dp[0][0] = 1;
	for (int i = 1; i <= n; ++i) {
		// dp[i][0]
		if (g[0][i] == '#' && g[1][i] == '#') dp[i][0] = dp[i - 1][0];
		else if (g[0][i] == '.' && g[1][i] == '.') {
			dp[i][0] = dp[i - 1][0];
			if (i > 1 && g[0][i - 1] == '.' && g[1][i - 1] == '.') dp[i][0] += dp[i - 2][0];
			dp[i][0] = min(dp[i][0], 2);
		}
		else if (g[0][i] == '#' && g[1][i] == '.') {
			if (i > 1 && g[1][i - 1] == '.') dp[i][0] = dp[i - 1][1]; // 上凸
		}
		else {
			if (i > 1 && g[0][i - 1] == '.') dp[i][0] = dp[i - 1][2]; // 下凸
		}
		// dp[i][1]
		if (g[0][i] == '#') dp[i][1] = dp[i - 1][0];
		else {
			if (i > 1 && g[0][i - 1] == '.') dp[i][1] = dp[i - 1][2];
		}
		// dp[i][2]
		if (g[1][i] == '#') dp[i][2] = dp[i - 1][0];
		else {
			if (i > 1 && g[1][i - 1] == '.') dp[i][2] = dp[i - 1][1];
		}
	}
	if (dp[n][0]) {
		if (dp[n][0] > 1) cout << "Multiple" << '\n';
		else cout << "Unique" << '\n';
	}
	else {
		cout << "None" << '\n';
	}
}

int main() {
	ios::sync_with_stdio(false); cin.tie(nullptr);
	int t;
	cin >> t;
	while (t--) solve();
}