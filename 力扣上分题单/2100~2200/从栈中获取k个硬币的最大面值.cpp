// https://leetcode.cn/problems/maximum-value-of-k-coins-from-piles/



class Solution {
public:
    int maxValueOfCoins(vector<vector<int>>& piles, int k) {
        // 这是一个分组背包问题，但是是否可以优化时间复杂度?
        // 奇怪的是LeetCode这道题数据几下就过了
    	int n = piles.size(), sum[n][2010], dp[k + 1];
    	memset(dp, 0, sizeof(dp)); 
    	memset(sum, 0, sizeof(sum));
    	for (int i = 0; i < n; ++i)
    		for (int j = 1; j <= piles[i].size(); ++j) 
    			sum[i][j] = sum[i][j - 1] + piles[i][j - 1];
    	for (int i = 0; i < n; ++i) 
    		for (int j = k; j >= 0; --j)
    			for (int x = 0; x <= min(j, (int)piles[i].size()); ++x)
    				dp[j] = max(dp[j], dp[j - x] + sum[i][x]);
    	return dp[k];
    }
};