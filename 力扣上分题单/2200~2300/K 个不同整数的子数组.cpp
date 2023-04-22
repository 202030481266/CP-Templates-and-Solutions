// https://leetcode.cn/problems/subarrays-with-k-different-integers/
// 容斥原理 + 滑动窗口



class Solution {
public:
    int subarraysWithKDistinct(vector<int>& nums, int k) {
    	int n = nums.size(), cnt[n + 1];
    	// 计算包含最多K个不同数字的子数组个数
    	auto f = [&](int K) -> int {
    		int l = 0, type = 0, res = 0;
    		memset(cnt, 0, sizeof(cnt));
    		for (int i = 0; i < n; ++i) {
    			++cnt[nums[i]];
    			if (cnt[nums[i]] == 1) ++type;
    			while (type > K) {
    				res += (i - l); //[l,i-1]
    				--cnt[nums[l]];
    				if (cnt[nums[l++]] == 0) --type;
    			}
    		}
    		while (l < n) res += (n - l), ++l;
    		return res;
    	};
    	return f(k) - f(k - 1);
    }
};