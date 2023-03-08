// https://leetcode.cn/problems/longest-turbulent-subarray/



class Solution {
public:
    int maxTurbulenceSize(vector<int>& arr) {
    	int n =  arr.size();
    	vector dp(n + 1, vector<int>(2, 0));

    	int ans = 1;
    	dp[1][0] = dp[1][1] = 1;
    	for (int i = 2; i <= n; ++i) {
    		dp[i][1] = dp[i][0] = 1;
    		if (arr[i - 2] > arr[i - 1]) {
    			if (dp[i - 1][0] > 0 && (dp[i - 1][0] - 1) % 2 == 0) dp[i][0] = dp[i - 1][0] + 1;
    			if (dp[i - 1][1] > 0 && (dp[i - 1][1] - 1) % 2 == 1) dp[i][1] = dp[i - 1][1] + 1;
    			dp[i][0] = max(dp[i][0], 2); // a > b
    		}
    		if (arr[i - 2] < arr[i - 1]) {
    			if (dp[i - 1][0] > 0 && (dp[i - 1][0] - 1) % 2 == 1) dp[i][0] = dp[i - 1][0] + 1;
    			if (dp[i - 1][1] > 0 && (dp[i - 1][1] - 1) % 2 == 0) dp[i][1] = dp[i - 1][1] + 1;
    			dp[i][1] = max(dp[i][1], 2); // a < b
    		}
    		ans = max({ans, dp[i][1], dp[i][0]});
    	}
    	return ans;
    }
};