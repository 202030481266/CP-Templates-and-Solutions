// https://leetcode.cn/problems/constrained-subsequence-sum/
// 经典的单调队列优化的动态规划题目


class Solution {
public:
    int constrainedSubsetSum(vector<int>& nums, int k) {
        // dp[i] = max{dp[j] + nums[i]} i-k<=j<=i-1
        // 单调队列优化

        int n = nums.size();
        vector<int> dp(n + 1);
        vector<int> Q(n + 1);
        int st = 0;
        int ed = 0;
        Q[ed++] = 0;
        dp[0] = nums[0];
        for (int i = 1; i < n; ++i) {
            // the i-k<=j<=i-1
            dp[i] = max(dp[Q[st]], 0) + nums[i];
            // update the queue
            while (st < ed && dp[i] > dp[Q[ed - 1]]) --ed;
            Q[ed++] = i;
            while (st < ed && Q[st] < i - k + 1) ++st;
        }
        int ans = INT_MIN;
        for (int i = 0; i < n; ++i) {
            ans = max(ans, dp[i]);
        }
        return ans;
    }
};