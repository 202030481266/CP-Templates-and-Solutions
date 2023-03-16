// https://leetcode.cn/problems/stone-game/



class Solution {
public:
	bool stoneGame(vector<int>& piles) {
		int n = piles.size();
		vector dp(n + 1, vector(n + 1, vector<int>(2, 0)));

		for (int i = 0; i < n; ++i)
			dp[i][i][0] = piles[i], dp[i][i][1] = -piles[i];
		for (int len = 2; len <= n; ++len) {
			for (int i = 0; i + len - 1 < n; ++i) {
				int j = i + len - 1;
				dp[i][j][0] = max(piles[i] - dp[i + 1][j][1], piles[j] - dp[i][j - 1][1]);
				dp[i][j][1] = max(piles[i] - dp[i + 1][j][0], piles[j] - dp[i][j - 1][0]);
			}
		}
		if (dp[0][n - 1][0] > 0) return true;
		return false;
	}
};