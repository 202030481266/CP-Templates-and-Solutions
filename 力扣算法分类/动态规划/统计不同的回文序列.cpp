// https://leetcode.cn/problems/count-different-palindromic-subsequences/



class Solution {
public:
	static constexpr int mod = 1e9 + 7;
	int countPalindromicSubsequences(string s) {
		int n = s.size();
		// a...a, b...b, c...c, d...d
		vector dp(4, vector(n + 1, vector<long long>(n + 1)));
		for (int i = 0; i < n; ++i)
			dp[s[i] - 'a'][i][i] = 1;
		for (int len = 2; len <= n; ++len) {
			for (int i = 0; i + len - 1 < n; ++i) {
				int j = i + len - 1;
				for (int k = 0; k < 4; ++k) {
					if (s[i] == s[j] && s[i] - 'a' == k) {
						dp[k][i][j] = (2 + dp[0][i + 1][j - 1] + dp[1][i + 1][j - 1] + dp[2][i + 1][j - 1] + dp[3][i + 1][j - 1]) % mod;
					}
					else if (s[i] - 'a' == k) {
						dp[k][i][j] = dp[k][i][j - 1];
					}
					else if (s[j] - 'a' == k) {
						dp[k][i][j] = dp[k][i + 1][j];
					}
					else {
						dp[k][i][j] = dp[k][i + 1][j - 1];
					}
				}
			}
		}
		long long ans = 0;
		for (int i = 0; i < 4; ++i)
			ans = (ans + dp[i][0][n - 1]) % mod;
		return ans;
	}
};