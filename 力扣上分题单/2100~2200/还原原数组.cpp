// https://leetcode.cn/problems/recover-the-original-array/



class Solution {
public:
    vector<int> recoverArray(vector<int>& nums) {
    	sort(nums.begin(), nums.end());
    	int n = nums.size(), sub = 0;
    	unordered_map<int, int> cnt;
    	// 确定了公差2*k那么就可以非常简单
    	for (const int& v : nums) ++cnt[v];
    	for (int i = 1; i < n; ++i) {
    		sub = nums[i] - nums[0];
    		if (sub & 1 || sub == 0) continue;
    		// 检查匹配
    		unordered_map<int, int> tmp(cnt);
    		bool flag = true;
    		for (int j = 0; j < n; ++j) {
    			// 还有这个数字
    			if (tmp[nums[j]]) {
    				--tmp[nums[j]];
    				if (tmp[nums[j] + sub]) --tmp[nums[j] + sub];
    				else { flag = false; break; }
    			}
    		}
    		if (flag) break;
    	}
    	vector<int> ans;
    	for (int i = 0; i < n; ++i) {
    		if (cnt[nums[i]]) {
    			--cnt[nums[i]];
    			--cnt[nums[i] + sub];
    			ans.emplace_back((nums[i] * 2 + sub) / 2);
    		}
    	}
    	return ans;
    }
};