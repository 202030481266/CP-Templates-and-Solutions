// https://leetcode.cn/problems/longest-arithmetic-subsequence-of-given-difference/
// 分类讨论一下就可以了，difference=0的时候所有的数字都是一样的，所以统计，否则所有数都是不一样的可以DP


class Solution {
public:
    int longestSubsequence(vector<int>& arr, int difference) {
    	int n = arr.size();

        

    	// 开头确定,整个序列的长度就已经知道了
    	unordered_map<int,int> dp;
    	int ans = 1;

        if (difference == 0) {
            for (auto c : arr) ++dp[c];
            int ans = 0;
            for (auto c : arr) {
                ans = max(ans, dp[c]);
            }
            return ans;
        }

    	for (auto c : arr) {
            dp[c] = 1;
    		if (dp.count(c - difference))
    			dp[c] += dp[c - difference];
    		ans = max(ans, dp[c]);
    	}

    	return ans;
    }
};