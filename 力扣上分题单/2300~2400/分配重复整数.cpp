// https://leetcode.cn/problems/distribute-repeating-integers/
// dp+二进制（实在没有找到更加优秀的算法，感觉还是暴力）


class Solution {
	typedef pair<int, int> pii;
public:
    bool canDistribute(vector<int>& nums, vector<int>& quantity) {
    	int m = quantity.size();
    	vector<int> cnt(1010), sum(1 << m);
    	for (int c : nums) ++cnt[c];
    	vector<pii> a;
    	for (int i = 1; i <= 1000; ++i) if (cnt[i]) a.emplace_back(i, cnt[i]);
    	for (int i = 1; i < (1 << m); ++i) 
    		for (int j = 0; j < m; ++j) if ((i >> j) & 1) sum[i] += quantity[j];
    	// 二进制+背包
    	int n = a.size();
    	vector<bool> dp(1 << m, false);
    	dp[0] = true;
    	for (int i = 0; i < n; ++i) 
    		for (int j = (1 << m) - 1; j >= 1; --j) 
    			for (int sub = j; sub > 0; sub = (sub - 1) & j) 
    				if (sum[sub] <= a[i].second) dp[j] = (dp[j] || dp[j ^ sub]);
    	return dp.back();
	}
};