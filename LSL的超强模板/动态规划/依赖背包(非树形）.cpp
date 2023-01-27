vector<int> Dp_rely(int T, vector<int> w, vector<int> v, vector<vector<vector<int>>> rely) {
	// start from 1 to n
	// T 是总质量
	// rely[i] 表示第i个主物品的依赖物品
	// 采用分配限制的原则来获得最大价值
	int n = w.size();
	vector<int> dp(T + 1);
	for (int i = 1; i <= n; i++) {
		// 01背包获得附件分配限制后的最大价值
		vector<int> f(T + 1, 0);
		for (auto [_w, _v] : rely[i])
			for (int j = T - w[i]; j >= _w; j--)
				f[j] = max(f[j], f[j - _w] + _v);
		f[T] = f[T - w[i]] + v[i];
		for (int j = T; j >= 0; j--)
			for (int k = w[i]; k <= T; k++)
				// 分配限制k给组i
				if (j - k >= 0) 
					dp[j] = max(dp[j], dp[j - k] + f[k - w[i]] + v[i]);
	}
	return dp;
}