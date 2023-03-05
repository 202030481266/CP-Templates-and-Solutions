// https://leetcode.cn/problems/2-keys-keyboard/



class Solution {
public:
    int minSteps(int n) {
    	vector<int> dp(n + 1, INT_MAX);
    	dp[1] = 0;

    	for (int i = 2; i <= n; ++i)
    		for (int j = 1; j <= (i / 2); ++j) {
    			if ((i % j) == 0) {
    				// step length is j, and steps is i / j which at least is 2;
    				dp[i] = min(dp[i], dp[j] + i / j);
    			}
    		}
    	return dp[n];
    }
};