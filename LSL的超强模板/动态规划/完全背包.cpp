vector<int> Dp_complete(int T, vector<int> w, vector<int> v) {
	// start from 1 to n;
	// T 是总质量
	int n = w.size();
	vector<int> dp(T + 1);
	for (int i = 1; i <= n; i++)
		for (int j = w[i]; j <= T; j++)
			dp[j] = max(dp[j], dp[j - w[i]] + v[i]);
	return dp;
}