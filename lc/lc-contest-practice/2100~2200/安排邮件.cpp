// https://leetcode.cn/problems/allocate-mailboxes/



class Solution {
public:
    int minDistance(vector<int>& houses, int k) {
    	// 1 <= n <= 100
    	int n = houses.size(), dp[n + 1][k + 1], cost[n + 1][n + 1]; 
    	if (k >= n) return 0;
    	memset(dp, 0x3f, sizeof(dp));
    	memset(cost, 0, sizeof(cost));
    	sort(houses.begin(), houses.end());
    	for (int i = 1; i <= n; ++i)
    		for (int j = i; j <= n; ++j) {
    			int median;
    			if ((i + j) % 2 == 0) median = houses[(i + j) / 2 - 1];
    			else median = (houses[(i + j) / 2 - 1] + houses[(i + j + 1) / 2 - 1]) / 2;
    			for (int x = i; x <= j; ++x) cost[i][j] += abs(median - houses[x - 1]);
    		}
    	for (int i = 0; i <= k; ++i) dp[0][i] = 0; // 没有损耗
    	for (int i = 1; i <= n; ++i) {
    		for (int j = 1; j <= k; ++j) {
    			if (j >= i) dp[i][j] = 0;
    			else {
    				// 枚举最后一个放的邮筒覆盖的房间号码
    				for (int l = i; l >= 1; --l) {
    					// [l,i]
    					dp[i][j] = min(dp[l - 1][j - 1] + cost[l][i], dp[i][j]);
    				}
    			}
    		}
    	}
    	return dp[n][k];
    }
};