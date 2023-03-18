// https://leetcode.cn/problems/count-number-of-maximum-bitwise-or-subsets/
// 朴素的二进制暴力搜索，没有任何的转换技巧


class Solution {
public:
	int countMaxOrSubsets(vector<int>& nums) {
		int mx = 0;
		int n = nums.size();
		for (auto c : nums) mx = mx | c;

		int N = (1 << n);
		int ans = 0;
		vector<int> dp(N);
		unordered_map<int, int> h;
		for (int i = 0; i <= 20; ++i) h[(1 << i)] = i;
		for (int i = 1; i < N; ++i) {
			int s = (i & (-i));
			int prev = i - s, idx = h[s];
			dp[i] = dp[prev] | nums[idx];
			if (dp[i] == mx) ++ans;
		}
		return ans;
	}
};