// https://leetcode.cn/problems/minimum-number-of-operations-to-make-array-continuous/
// 二分难题，考虑最多能够保留的区间[l, r]


class Solution {
public:
    int minOperations(vector<int>& nums) {
    	int n = nums.size();
    	sort(nums.begin(), nums.end());
    	nums.erase(unique(nums.begin(), nums.end()), nums.end());

    	// reserve the number on [l, r]
    	// need the numbers of nums[r] - nums[l] + 1 - (r - l + 1)
    	// and we have can the remain number n - (r + l - 1)
    	// so we can get nums[l] >= nums[r] - n + 1
    	// for every r we find the smallest one l that satisfy this formula

    	int ans = n;
    	for (int i = 0; i < nums.size(); ++i) {
    		int tmp = nums[i] - n + 1;
    		auto it = lower_bound(nums.begin(), nums.end(), tmp);
    		if (it != nums.end()) {
    			int p = it - nums.begin();
    			if (p <= i) {
    				ans = min(ans, n - (i - p + 1));
    			}
    		}
    	}
    	return ans;
    }
};