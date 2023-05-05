// https://leetcode.cn/problems/number-of-subsequences-that-satisfy-the-given-sum-condition/



class Solution {
	static constexpr int mod = 1000000007;
public:
	int pow_mod(int x, int n) {
	    int res = 1;
	    for (long long p = x; n > 0; n >>= 1, p = (p * p) % mod)
	        if ((n & 1) != 0)
	            res = (int)(res * p % mod);
	    return res;
	}
    int numSubseq(vector<int>& nums, int target) {
    	sort(nums.begin(), nums.end());
    	long long ans = 0, n = nums.size();
    	for (int i = 0; i < n; ++i) {
    		int pos = upper_bound(nums.begin(), nums.end(), target - nums[i]) - nums.begin();
    		if (pos - 1 >= i) {
    			// [0, i - 1] 子集
    			ans = (ans + pow_mod(2, i)) % mod;
    		}
    		else if (pos - 1 >= 0) {
    			// [0, pos-1] 是非空子集 + [pos, i - 1]子集，i必选 
    			if (i - 1 >= pos)
    				ans = (ans + 1ll * (pow_mod(2, pos) - 1) * pow_mod(2, i - pos) % mod + mod) % mod;
    			else ans = (ans + pow_mod(2, pos) - 1 + mod) % mod;
    		}
    	}
    	return ans;
    }
};