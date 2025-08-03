#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;

static constexpr int maxn = 5003;
static constexpr int inf = 0x3f3f3f3f;
static constexpr ll llinf = 0x3f3f3f3f3f3f3f3f;
static constexpr int mod = 1e9 + 7;

int n;
int cnt[maxn];
int dp[maxn][maxn];
char s[maxn];

int main() {
	scanf("%s", s + 1);
	n = strlen(s + 1);
	for (int i = 1; i <= n; ++i) cin >> s[i];
	for (int len = 1; len <= n; ++len) {
		for (int i = 1; i + len - 1 <= n; ++i) {
			int j = i + len - 1;
			if (len == 1) dp[i][j] = 1;
			else if (len == 2) dp[i][j] = (s[i] == s[j] ? 2 : 0);
			else {
				if (s[i] == s[j] && dp[i + 1][j - 1]) {
					dp[i][j] = 1;
					if (len & 1) {
						if (dp[i + len / 2 + 1][j]) dp[i][j] = dp[i + len / 2 + 1][j] + 1;
					}
					else {
						if (dp[i + len / 2][j]) dp[i][j] = dp[i + len / 2][j] + 1;
					}
				}
			}
			if (dp[i][j]) {
				cnt[1]++;
				cnt[dp[i][j] + 1]--;
			}
		}
	}
	for (int i = 2; i <= n; ++i) cnt[i] += cnt[i - 1];
	for (int i = 1; i <= n; ++i) cout << cnt[i] << ' ';
}