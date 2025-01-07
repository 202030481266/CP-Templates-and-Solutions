// https://leetcode.cn/problems/number-of-ways-to-wear-different-hats-to-each-other/
// 01背包 + 二进制优化


class Solution {
	static constexpr int mod = 1000000007;
	typedef long long ll;
public:
    int numberWays(vector<vector<int>>& hats) {
    	// 匹配方案数问题，显然的方法是使用dfs爆搜，但是搜索空间非常巨大，大概5个人是极限了
    	// 但似乎可以反着来，人明显最多10个，那么就可以反着匹配
    	int n = hats.size(), dp[1 << n];
    	vector<int> g[50];
    	for (int i = 0; i < n; ++i)
    		for (int v : hats[i]) g[v].emplace_back(i);
    	memset(dp, 0, sizeof(dp));
    	dp[0] = 1;
    	for (int i = 1; i <= 40; ++i) 
    		for (int j = (1 << n) - 1; j >= 1; --j) 
    			for (int u : g[i])
    				if ((j >> u) & 1) 
    					dp[j] = (dp[j] + dp[j ^ (1 << u)]) % mod;
    	return dp[(1 << n) - 1];
    }
};