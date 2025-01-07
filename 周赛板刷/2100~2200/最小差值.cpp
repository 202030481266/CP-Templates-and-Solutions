// https://leetcode.cn/problems/smallest-range-ii/
// 技巧： 划分区间，一边加一边减


class Solution {
public:
    int smallestRangeII(vector<int>& nums, int k) {
			int n = nums.size();
    	if (n == 1) return 0;
    	// 贪心，对于大的数选择减少，对于小的数字选择增加
    	sort(nums.begin(), nums.end());
    	int ans = nums.back() - nums[0]; // 全部加或者全部减
    	for (int i = 0; i < n - 1; ++i) {
    		// 0... i 增加， i+1...n-1 减少
    		int mx = max(nums[i] + k, nums[n - 1] - k);
    		int mn = min(nums[0] + k, nums[i + 1] - k);
    		ans = min(ans, mx - mn);
    	}
    	return ans;
    }
};