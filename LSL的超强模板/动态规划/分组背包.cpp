vector<vector<int>> Dp_group(int T, vector<vector<vector<int>>> group) {
	// start from 1 to n
	// group[i] 表示第i组的物品
	// group[i][j] 表示第i组的第j个物品的信息
	int g = group.size();
	vector<vector<int>> dp(g + 1, vector<int>(T + 1));
	for (int i = 1; i <= g; i++) 
		for (int j = T; j >= 0; j--) {
			for (auto [w, v] : group[i]) {
				if (j - w >= 0) dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - w] + v);
				else dp[i][j] = dp[i - 1][j];
			}
		}
	return dp;
}