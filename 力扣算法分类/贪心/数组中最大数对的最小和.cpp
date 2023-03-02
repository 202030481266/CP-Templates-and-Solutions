// https://leetcode.cn/problems/minimize-maximum-pair-sum-in-array/



class Solution {
public:
    int minPairSum(vector<int>& nums) {
    	sort(nums.begin(), nums.end());

    	int l = 0, r = nums.size() - 1;
    	int ans = INT_MIN;
    	while (l < r) 
    		ans = max(ans, nums[l++] + nums[r--]);
    	return ans;
    }
};