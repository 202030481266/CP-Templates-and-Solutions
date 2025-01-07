// https://leetcode.cn/problems/count-subarrays-with-fixed-bounds/



class Solution {
public:
    long long countSubarrays(vector<int>& nums, int minK, int maxK) {
    	long long ans = 0;
			int a = -1, b = -1, c = -1;
    	for (int i = 0; i < nums.size(); ++i) {
    		int x = nums[i];
    		if (x == maxK) b = i;
    		if (x == minK) a = i;
    		if (x < minK || x > maxK) c = i;
    		ans += max(0, min(a, b) - c);
    	}
    	return ans;
    }
};