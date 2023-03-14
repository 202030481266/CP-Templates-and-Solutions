// https://leetcode.cn/problems/maximum-sum-of-3-non-overlapping-subarrays/
// 创新点在于逆状态寻找方案


class Solution {
public:
    vector<int> maxSumOfThreeSubarrays(vector<int>& nums, int k) {
    	int n = nums.size();
    	vector dp(n + 1, vector<int>(4));
    	vector pre(n + 1, vector<pair<int, int>>(4));
    	vector<int> sum(n + 1);
    	vector<int> pos(3);

    	for (int i = 1; i <= n; ++i)
    		sum[i] = sum[i - 1] + nums[i - 1];
    	for (int i = k; i <= n; ++i) {
    		for (int j = 1; j <= 3; ++j) {
    			dp[i][j] = dp[i - 1][j];
    			pre[i][j] = make_pair(i - 1, j);
    			if (dp[i - k][j - 1] > 0 || j == 1) {
	    			int t = dp[i - k][j - 1] + sum[i] - sum[i - k];
	    			if (t > dp[i][j]) {
	    				pre[i][j] = make_pair(i - k, j - 1);
	    				dp[i][j] = t;
	    			}
	    		}
    		}
    	}
    	auto cur = pre[n][3];
    	for (int i = 3; i >= 1; --i) {
    		while (cur.second == i) cur = pre[cur.first][cur.second];
    		pos[i - 1] = cur.first;
    	}
    	return pos;
    }
};