// https://leetcode.cn/problems/maximum-score-from-performing-multiplication-operations/



class Solution {
public:
    int maximumScore(vector<int>& nums, vector<int>& multipliers) {
    	int n = nums.size(), m = multipliers.size();
    	vector dp(m, vector<int>(m, -1));
    	function<int(int, int)> dfs = [&](int l, int r) -> int {
    		if (l + r == m) return 0;
    		if (dp[l][r] != -1) return dp[l][r];
    		int cur = l + r;
    		int res = INT_MIN;
    		res = max(multipliers[cur] * nums[l] + dfs(l + 1, r), 
    			multipliers[cur] * nums[n - 1 - r] + dfs(l, r + 1));
    		return dp[l][r] = res;
    	};
    	return dfs(0, 0);
    }
};