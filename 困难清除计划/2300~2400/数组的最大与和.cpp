// https://leetcode.cn/problems/maximum-and-sum-of-array/



// 二进制爆搜超时
class Solution {
public:
    int maximumANDSum(vector<int>& nums, int numSlots) {
    	// 最多的搜索次数 5*10^6
    	int n = nums.size(), dp[1 << n][numSlots * 2];
    	// 桶 1 2 3 ... numslots 1 2 3... 每一个桶只能装一个
    	memset(dp, -1, sizeof(dp));
    	function<int(int, int)> dfs = [&](int s, int p) -> int {
    		if (p > 2 * numSlots) return 0;
    		int &res = dp[s][p];
    		if (res != -1) return res; 
    		res = 0;
    		int idx = (p % numSlots == 0 ? numSlots : p % numSlots);
    		// 不填
    		res = max(res, dfs(s, p + 1));
    		// 填
    		for (int i = 0; i < n; ++i) 
    			if (s & (1 << i))
    				res = max(res, (nums[i] & idx) + dfs(s ^ (1 << i), p + 1));
    		return res;
    	};
    	return dfs((1 << n) - 1, 1);
    }
};


// 考虑三进制的压缩
class Solution {
public:
    int maximumANDSum(vector<int>& nums, int numSlots) {
        int n = nums.size();
        int mask_max = 1;
        for (int i = 0; i < numSlots; ++i) {
            mask_max *= 3;
        }
        vector<int> f(mask_max);
        for (int mask = 1; mask < mask_max; ++mask) {
            int cnt = 0;
            for (int i = 0, dummy = mask; i < numSlots; ++i, dummy /= 3) {
                cnt += dummy % 3;
            }
            if (cnt > n) {
                continue;
            }
            for (int i = 0, dummy = mask, w = 1; i < numSlots; ++i, dummy /= 3, w *= 3) {
                int has = dummy % 3;
                if (has) {
                    f[mask] = max(f[mask], f[mask - w] + (nums[cnt - 1] & (i + 1)));
                }
            }
        }
        
        return *max_element(f.begin(), f.end());
    }
};
