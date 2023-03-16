// https://leetcode.cn/problems/guess-number-higher-or-lower-ii/



class Solution {
public:
	int getMoneyAmount(int n) {
		vector dp(n + 1, vector<int>(n + 1, -1));
		function<int(int, int)> dfs = [&](int l, int r) -> int {
			if (l >= r) return 0;
			if (l == r - 1) return l;
			if (dp[l][r] != -1) return dp[l][r];
			int tmp = INT_MAX;
			for (int i = l; i <= r; ++i) {
				tmp = min(tmp, max(dfs(l, i - 1), dfs(i + 1, r)) + i);
			}
			return dp[l][r] = tmp;
		};
		return dfs(1, n);
	}
};