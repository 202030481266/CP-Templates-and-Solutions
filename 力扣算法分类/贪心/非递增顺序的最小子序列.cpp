// https://leetcode.cn/problems/minimum-subsequence-in-non-increasing-order/



class Solution {
public:
    vector<int> minSubsequence(vector<int>& nums) {
    	int sum = accumulate(nums.begin(), nums.end(), 0);

    	sort(nums.begin(), nums.end());
    	int n = nums.size();
    	int p = n - 1;
    	int cur = 0;
    	vector<int> ans;
    	while (p >= 0 && cur <= sum) {
    		sum -= nums[p];
    		cur += nums[p];
    		ans.emplace_back(nums[p--]);
    	}
    	return ans;
    }
};