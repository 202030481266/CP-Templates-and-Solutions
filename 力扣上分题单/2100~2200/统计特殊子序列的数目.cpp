// https://leetcode.cn/problems/count-number-of-special-subsequences/



class Solution {
public:
	static constexpr int mod = 1000000007; 
    int countSpecialSubsequences(vector<int>& nums) {
    	int n = nums.size();

    	int a = 0, b = 0, c = 0;
    	for (int i = 0; i < n; ++i) {
    		if (nums[i] == 0) {
    			// not use is a, and use it as a
					a = ((a * 2) % mod + 1) % mod;
    		}
    		else if (nums[i] == 1) {
    			if (a) {
    				// use 1
    				b = ((b * 2) % mod + a) % mod;
    			}
    		}
    		else {
    			if (b) {
    				// use 2
    				c = ((c * 2) % mod + b) % mod;
    			}
    		}
    	}
    	return c % mod;
    }
};