// https://leetcode.cn/problems/ways-to-split-array-into-three-subarrays/



class Solution {
public:
	static constexpr int mod = 1000000007;
    int waysToSplit(vector<int>& nums) {
    	int n = nums.size();

    	vector<int> sum(n);
    	sum[0] = nums[0];
    	// increasing
    	for (int i = 1; i < n; ++i) {
    		sum[i] = sum[i - 1] + nums[i];
    	}

    	long long ans = 0;
    	for (int i = 0; i < n; ++i) {
    		if (sum[n - 1] < 3 * sum[i]) break;
    		// [0...i] is the left part
    		auto x = lower_bound(sum.begin() + i + 1, sum.end(), 2 * sum[i]);
            if (x == nums.end()) {
    			break;
    		}
    		auto y = upper_bound(x, sum.end(), (sum[n - 1] + sum[i]) / 2);
    		int l = x - sum.begin(), r = y - sum.begin();
            r = min(n - 1, r); // r is at most n - 1;
            if (r > l) 
            	// only r > l can be add the result
    			ans = (ans + (r - l)) % mod;
    	}
    	return ans;
    }
};