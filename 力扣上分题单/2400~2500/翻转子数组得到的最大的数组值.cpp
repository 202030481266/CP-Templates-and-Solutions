// https://leetcode.cn/problems/reverse-subarray-to-maximize-array-value/
// 构造题目思维


class Solution {
public:
    int maxValueAfterReverse(vector<int>& nums) {
    	int n = nums.size(), res = 0, ans = 0;
    	for (int i = 0; i < n - 1; ++i) ans += abs(nums[i] - nums[i + 1]);
    	if (n <= 2) return ans;
    	for (int i = 1; i < n - 1; ++i)  {
    		// 翻转 [0, i] 或者 [i, n-1]
    		res = max(res, abs(nums[i + 1] - nums[0]) - abs(nums[i] - nums[i + 1]));
    		res = max(res, abs(nums[n - 1] - nums[i - 1]) - abs(nums[i] - nums[i - 1]));
    	}
    	// s,t都不在两端上
    	int left = min(nums[1], nums[0]), right = max(nums[1], nums[0]);
    	for (int i = 2; i < n - 1; ++i) {
    		int l = min(nums[i], nums[i + 1]), r = max(nums[i], nums[i + 1]);
    		if (left > r) res = max(res, 2 * (left - r));
    		if (right < l) res = max(res, 2 * (l - right));
    		left = max(left, min(nums[i], nums[i - 1]));
    		right = min(right, max(nums[i], nums[i - 1]));
    	}
    	return ans + res;
    }
};