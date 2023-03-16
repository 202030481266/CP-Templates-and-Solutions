// https://leetcode.cn/problems/count-different-palindromic-subsequences/



class Solution {
public:
	static constexpr int mod = 1e9 + 7;
	int countPalindromicSubsequences(string s) {
		int n = s.size();
		vector dp(n + 1, vector<long long>(n + 1));
		vector pre(n + 1, vector<int>(4, -1));
		vector nxt(n + 1, vector<int>(4, -1));
		vector<int> pos(4);

		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < 4; ++j) {
				pre[i][j] = pos[j];
			}
			pos[s[i] - 'a'] = i;
		}
		fill(pos.begin(), pos.end(), n);
		for (int i = n - 1; i >= 0; --i) {
			for (int j = 0; j < 4; ++j) {
				nxt[i][j] = pos[j];
			}
			pos[s[i] - 'a'] = i;
		}
		for (int i = 0; i < n; ++i)
			dp[i][i] = 1;
		for (int len = 2; len <= n; ++len) {
			for (int i = 0; i + len - 1 < n; ++i) {
				int j = i + len - 1;
				if (s[i] == s[j]) {
					int k = s[i] - 'a';
					int l = nxt[i][k], r = pre[j][k];
					if (l > r) {
						dp[i][j] = (2ll + 2 * dp[i + 1][j - 1]) % mod;
					}
					else if (l == r) {
						dp[i][j] = (1ll + 2 * dp[i + 1][j - 1]) % mod;
					}
					else {
						dp[i][j] = (2 * dp[i + 1][j - 1] - dp[l + 1][r - 1] + mod) % mod;
					}
				}
				else {
					dp[i][j] = (dp[i + 1][j] + dp[i][j - 1] - dp[i + 1][j - 1] + mod) % mod;
				}
			}
		}
		return dp[0][n - 1];
	}
};