#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;

static constexpr int maxn = 100005;
static constexpr int inf = 0x3f3f3f3f;

int n, dp[maxn], f[maxn], arr[maxn];

int main() {
	ios::sync_with_stdio(false); cin.tie(NULL);
	cin >> n;
	for (int i = 1; i <= n; ++i) cin >> arr[i];
	for (int i = 1; i <= n; ++i) {
		if (arr[i] > arr[i - 1]) dp[i] = dp[i - 1] + 1;
		else dp[i] = 1;
	}
	for (int i = n; i >= 1; --i) {
		if (arr[i + 1] > arr[i]) f[i] = f[i + 1] + 1;
		else f[i] = 1;
	}
	int ans = 1;
	for (int i = 1; i <= n; ++i) {
		if (i - 1 >= 1) ans = max(ans, dp[i - 1] + 1);
		if (i + 1 <= n) ans = max(ans, f[i + 1] + 1);
		if (i - 1 >= 1 && i + 1 <= n && arr[i + 1] - arr[i - 1] > 1) {
			ans = max(ans, 1 + dp[i - 1] + f[i + 1]);
		}
	}
	cout << ans << '\n';
}