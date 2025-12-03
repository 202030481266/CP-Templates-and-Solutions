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
	vector dp(n + 1, vector<bool>(n + 1, 0));
	vector<ll> cnt(n + 1);
	for (int len = 1; len <= n; ++len) {
		for (int i = 1; i + len - 1 <= n; ++i) {
			int j = i + len - 1;
			if (len == 1) dp[i][j] = 1;
			else if (len == 2) dp[i][j] = (s[i - 1] == s[j - 1]);
			else dp[i][j] = (s[i - 1] == s[j - 1]) && dp[i + 1][j - 1];
			if (dp[i][j]) ++cnt[j]; // add one palindrome
		}
	}
	ll ans = 0;
	for (int i = 1; i <= n; ++i) {
		cnt[i] += cnt[i - 1];
		for (int j = i; j >= 1; --j) {
			if (dp[j][i]) {
				ans += cnt[j - 1];
			}
		}
	}
	cout << ans << '\n';
}