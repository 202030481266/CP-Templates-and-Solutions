#include <bits/stdc++.h>

// 一种通用的dp状态优化技巧 + 回溯讨论

using namespace std;
using ll = long long;
using pii = pair<int, int>;

static constexpr int maxn = 50003;
static constexpr int inf = 0x3f3f3f3f;

char s1[maxn], s2[maxn];
int dp[maxn][105], nxt[maxn][26];

int main() {
	scanf("%s", s1 + 1);
	int n = strlen(s1 + 1);
	for (int i = 1; i <= n; ++i) s2[i] = s1[n + 1 - i];
	vector<int> pos(26, inf);
	for (int i = n; i >= 0; --i) {
		for (int j = 0; j < 26; ++j) nxt[i][j] = pos[j];
		if (i > 0) pos[s1[i] - 'a'] = i;
	}
	memset(dp, 0x3f, sizeof(dp));
	dp[0][0] = 0;
	for (int i = 1; i <= n; ++i) {
		for (int j = 0; j <= min(100, i); ++j) {
			dp[i][j] = dp[i - 1][j];
			if (j > 0 && dp[i - 1][j - 1] < inf) {
				dp[i][j] = min(dp[i][j], nxt[dp[i - 1][j - 1]][s2[i] - 'a']);
			}
		}
	}
	string ans;
	int max_len = 0, st;
	for (int i = min(100, n); i >= 1; --i) {
		if (dp[n][i] < inf) {
			max_len = i;
			break;
		}
	}
	if (max_len < 100) {
		for (int i = n; i >= 1 && max_len; --i) { 
			if (dp[i - 1][max_len - 1] < inf) {
				if (nxt[dp[i - 1][max_len - 1]][s2[i] - 'a'] == dp[i][max_len]) {
					ans.push_back(s2[i]);
					--max_len;
				}
			}
		}
		cout << ans << endl;
	}
	else {
		// 如果LCS大于等于100，那么最长回文子序列和LCS不等价
		// 只需要随便找到50个，然后乘以2拼接即可，并且保证可以找到
		for (int i = 1; i <= n; ++i) {
			if (dp[i][50] <= n - i) {
				st = i;
				break;
			}
		}
		max_len = 50;
		for (int i = st; i >= 1 && max_len; --i) {
			if (dp[i - 1][max_len - 1] < inf) {
				if (nxt[dp[i - 1][max_len - 1]][s2[i] - 'a'] == dp[i][max_len]) {
					ans.push_back(s2[i]);
					--max_len;
				}
			}
		}
		string rans = ans;
		reverse(rans.begin(), rans.end());
		cout << rans + ans << endl;
	}
}