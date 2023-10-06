// https://leetcode.cn/problems/largest-sum-of-averages/



class Solution {
public:
    double largestSumOfAverages(vector<int>& nums, int k) {
    	int n = nums.size();

    	vector<int> sum(n + 1);
    	for (int i = 1; i <= n; ++i)
    		sum[i] = sum[i - 1] + nums[i - 1];

    	auto f = [&](int l, int r) -> double {
    		double t = 1.0 * (sum[r] - sum[l - 1]);
    		return t / (r - l + 1);
    	};

    	vector dp(n + 1, vector<double>(k + 1));
    	for (int i = 1; i <= n; ++i) {
    		dp[i][1] = f(1, i);
    		for (int j = 2; j <= k; ++j) {
    			for (int x = j - 1; x < i; ++x) {
    				// x + 1 ~ i is the j interval
    				dp[i][j] = max(dp[i][j], dp[x][j - 1] + f(x + 1, i));
    			}
    		}
    	}
    	double ans = 0;
    	for (int i = 1; i <= k; ++i) ans = max(ans, dp[n][i]);
    	return ans;
    }
};