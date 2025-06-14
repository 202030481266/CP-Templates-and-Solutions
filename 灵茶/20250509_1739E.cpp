#include <bits/stdc++.h>

using namespace std;
using ll = long long;

static constexpr int inf = 0x3f3f3f3f;
static constexpr int maxn = 2e5 + 7;

int n;
int a[2][maxn];
int dp[2][maxn], f[2][maxn];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n;
	char ch;
	for (int i = 1; i <= n; ++i) {
		cin >> ch;
		a[0][i] = ch - '0';
	}
	for (int i = 1; i <= n; ++i) {
		cin >> ch;
		a[1][i] = ch - '0';
	}
	dp[0][n] = a[0][n] + a[1][n];
	dp[1][n] = a[0][n] + a[1][n];
	f[0][n] = dp[0][n];
	f[1][n] = dp[1][n];
	for (int i = n - 1; i >= 1; --i) {
		dp[0][i] = f[0][i + 1];
		dp[1][i] = f[1][i + 1];
		if (a[1][i]) dp[0][i] = max(dp[0][i], a[1][i] + a[1][i + 1] + (i + 2 <= n ? dp[1][i + 2] : 0));
		if (a[0][i]) dp[1][i] = max(dp[1][i], a[0][i] + a[0][i + 1] + (i + 2 <= n ? dp[0][i + 2] : 0));
		dp[0][i] += a[0][i];
		dp[1][i] += a[1][i];
		f[0][i] = max(dp[0][i], f[0][i + 1]);
		f[1][i] = max(dp[1][i], f[1][i + 1]);
	}
	cout << dp[0][1] << '\n';
}