// https://leetcode.cn/problems/partition-array-for-maximum-sum/



class Solution {
public:
    int maxSumAfterPartitioning(vector<int>& arr, int k) {
    	int n = arr.size();
    	vector f(n + 1, vector<int>(n + 1));

    	for (int i = 1; i <= n; ++i) {
    		int k = arr[i - 1];
    		for (int j = i; j <= n; ++j) {
    			k = max(k, arr[j - 1]);
    			f[i][j] = k;
    		}
    	}
    	vector dp(n + 1, vector<int>(k + 1, 0));
    	for (int i = 1; i <= n; ++i) {
    		for (int j = max(0, i - k); j < i; ++j) {
	    		int mx = 0;
	    		for (int x = 1; x <= k; ++x) mx = max(mx, dp[j][x]);
	    		dp[i][i - j] = max(dp[i][i - j], (i - j) * f[j + 1][i] + mx);
    		}
    	}
    	int ans = INT_MIN;
    	for (int i = 1; i <= k; ++i)
    		ans = max(ans, dp[n][i]);
    	return ans;
    }
};