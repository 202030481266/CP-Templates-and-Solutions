#include <bits/stdc++.h>

using namespace std;
using ll = long long;

static constexpr int maxn = 500005;
static constexpr ll inf = 5e10;

int n, d, k;
int x[maxn], s[maxn];
int q[maxn], ed, st;
ll dp[maxn];

bool check(int g) {
	int mn = g < d ? d - g : 1;
	for (int i = 1; i <= n; ++i) dp[i] = -inf;
	dp[0] = 0;
	ed = st = 0;
	int p = 0;
	ll ans = 0;
	for (int i = 1; i <= n; ++i) {
		while (p <= n && x[i] - x[p] >= mn) {
			while (st < ed && dp[p] >= dp[q[ed - 1]]) ed--;
			q[ed++] = p++;
		}
		while (st < ed && x[i] - x[q[st]] > d + g) ++st;
		if (st < ed) dp[i] = max(dp[i], dp[q[st]] + s[i]);
		ans = max(ans, dp[i]);
	}
	return ans >= (ll)k;
}

int main() {
	ios::sync_with_stdio(false); cin.tie(nullptr);
	cin >> n >> d >> k;
	for (int i = 1; i <= n; ++i) cin >> x[i] >> s[i];
	int l = -1, r = max(d, x[n]) + 1;
	while (l + 1 < r) {
		int mid = (l + r) >> 1;
		if (check(mid)) r = mid;
		else l = mid;
	}
	cout << (r == max(d, x[n]) + 1 ? -1 : r) << '\n';
}