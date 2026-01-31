// https://leetcode.cn/problems/check-if-it-is-a-good-array/description/


class Solution {
public:
    bool isGoodArray(vector<int>& nums) {
    	// find some numbers that their gcd are 1
    	// if array satisfied this, so gcd(1, x) = 1, the arrays gcd is 1
    	int ans = nums[0];
    	for (int i = 1; i < nums.size(); ++i)
    		ans = __gcd(ans, nums[i]);
    	return ans == 1;
    }
};