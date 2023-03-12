// https://leetcode.cn/problems/largest-divisible-subset/



class Solution {
public:
    vector<int> largestDivisibleSubset(vector<int>& nums) {
    	sort(nums.begin(), nums.end());

    	int n = nums.size();
    	vector<int> dp(n + 1, 1);
    	vector<int> pre(n + 1, -1);

    	for (int i = 1; i < n; ++i) {
    		for (int j = 0; j < i; ++j) {
    			if (nums[i] % nums[j] == 0) {
    				if (dp[j] + 1 > dp[i]) {
    					pre[i] = j;
    					dp[i] = dp[j] + 1;
    				}
    			}
    		}
    	}
    	int ans = 0, index = -1;
    	for (int i = 0; i < n; ++i)
    		if (dp[i] > ans) {
    			ans = dp[i];
    			index = i;
    		}
    	vector<int> res;
    	while (index != -1) {
    		res.emplace_back(nums[index]);
    		index = pre[index];
    	}
    	return res;
    }
};