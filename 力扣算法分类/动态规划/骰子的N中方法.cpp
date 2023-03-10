// https://leetcode.cn/problems/number-of-dice-rolls-with-target-sum/



class Solution {
public:
	static constexpr int mod = 1000000007;
    int numRollsToTarget(int n, int k, int target) {
    	vector dp(n + 1, vector<int>(target + 1));

    	dp[0][0] = 1;
    	for (int i = 1; i <= n; ++i) {
    		for (int j = 1; j <= target; ++j) {
    			for (int x = 1; x <= min(j, k); ++x) {
    				if (x == j || dp[i - 1][j - x] > 0) {
    					dp[i][j] = (dp[i][j] + dp[i - 1][j - x]) % mod;
    				}
    			}
    		}
    	}
    	return dp[n][target];
    }
};