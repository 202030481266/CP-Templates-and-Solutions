//https://leetcode.cn/problems/minimum-replacements-to-sort-the-array/




class Solution {
public:
    long long minimumReplacement(vector<int>& nums) {
        int n = nums.size();

        long long ans = 0, pre = nums.back();
        for (int i = n - 1; i >= 1; --i) {
        	if (nums[i - 1] > pre) {
        		if (nums[i - 1] % pre == 0) {
        			// pre is not change
        			ans += (nums[i - 1] / pre - 1);
        		}
        		else {
        			// calulate the factor times
        			int x = nums[i - 1] / pre;
        			ans += x;
        			pre = nums[i - 1] / (x + 1);
        		}
        	}
        	else {
        		pre = nums[i - 1];
        	}
        }
        return ans;
    }
};