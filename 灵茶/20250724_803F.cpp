#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;

static constexpr int maxn = 100005;
static constexpr int mod = 1e9 + 7;

int n, m;
int cnt[maxn], a[maxn], b[maxn];
ll dp[maxn], pw[maxn];


int main() {
	ios::sync_with_stdio(false); cin.tie(NULL);
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
		++cnt[a[i]];
		m = max(m, a[i]);
	}
	for (int i = 2; i <= m; ++i) {
		for (int j = i; j <= m; j += i) {
			b[i] += cnt[j];
		}
	}
	pw[0] = 1;
	for (int i = 1; i <= n; ++i) pw[i] = pw[i - 1] * 2 % mod;
	ll tot = 0;
	for (int i = m; i >= 2; --i) {
		if (b[i]) {
			dp[i] = (pw[b[i]] - 1 + mod) % mod;
			for (int j = i + i; j <= m; j += i) {
				dp[i] = (dp[i] - dp[j] + mod) % mod;
			}
			tot = (tot + dp[i]) % mod;
		}
	}
	ll ans = ((pw[n] - 1 - tot) % mod + mod) % mod;
	cout << ans << '\n';
}
