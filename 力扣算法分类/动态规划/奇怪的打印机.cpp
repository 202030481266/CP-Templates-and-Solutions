// https://leetcode.cn/problems/strange-printer/
// 一开始的思路想的是覆盖一种字符然后分别对于不同覆盖字符进行累加和的区间dp
// 但是这是一个不容易发现的错误，其中存在非常特殊的情况，对于一次性全部覆盖来说更加优秀的解法


class Solution {
public:
	int strangePrinter(string s) {
		int n = s.size();
		vector dp(n + 1, vector<int>(n + 1, 0x3f3f3f3f));
		vector<bool> in(26);

		for (int len = 1; len <= n; ++len) {
			for (int i = 1; i + len - 1 <= n; ++i) {
				int j = i + len - 1;
				if (len == 1) dp[i][j] = 1;
				else {
					if (s[i - 1] == s[j - 1])
						dp[i][j] = dp[i][j - 1];
					else {
						for (int k = i; k < j; ++k)
							dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j]);
					}
				}
			}
		}
		// dbg(dp[1][n]);
		return dp[1][n];
	}
};