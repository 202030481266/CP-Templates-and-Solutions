vector<int> Dp_mix(int T, vector<int> w, vector<int> v, vector<int> num) {
	// start from 1 to n
	// T 是总质量
	// num 中 INT_MAX表示无数个
	int n = w.size();
	vector<int> dp(T + 1);
	for (int i = 1; i <= n; i++) {
		if (num[i] == 1) {
			// 01背包
			for (int j = T; j >= w[i]; j--)
				dp[j] = max(dp[j], dp[j - w[i]] + v[i]);
		} else if (num[i] == INT_MAX) {
			// 完全背包
			for (int j = w[i]; j <= T; j++) 
				dp[j] = max(dp[j], dp[j - w[i]] + v[i]);
		} else {
			// 多重背包
			for (int j = T; j >= 0; j--)
				for (int k = 1; k <= num[i]; k++)
					if (j - k * w[i] >= 0)
						dp[j] = max(dp[j], dp[j - k * w[i]] + k * v[i]);
		}
	}
	return dp;
}