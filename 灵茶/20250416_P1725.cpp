#include <bits/stdc++.h>
using namespace std;
using ll = long long;

static constexpr int maxn = 200005;
static constexpr int inf = 0x3f3f3f3f;

int q[maxn], dp[maxn], ed, st;
int n, L, R, arr[maxn];

int main() {
	ios::sync_with_stdio(false); cin.tie(nullptr);
	cin >> n >> L >> R;
	for (int i = 0; i <= n; ++i) cin >> arr[i];
	memset(dp, -0x3f, sizeof(dp));
	dp[0] = 0;
	int p = 0;
	for (int i = 1; i <= n; ++i) {
		while (p <= n && i - p >= L) {
			while (st < ed && dp[p] >= dp[q[ed - 1]]) --ed;
			q[ed++] = p++;
		}
		while (st < ed && i - q[st] > R) ++st;
		if (st < ed) dp[i] = dp[q[st]] + arr[i];
	}
	int ans = -inf;
	for (int i = n + 1 - R; i <= n; ++i) ans = max(ans, dp[i]);
	cout << ans << '\n';
}