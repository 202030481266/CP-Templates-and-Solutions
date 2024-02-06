class Solution {
public:
    int maxResult(vector<int>& nums, int k) {
        // dp[i] = max(dp[x]) + nums[i]; x in [max(0, i - k), max(0, i - 1)]
        // 单调队列优化DP
        
        int n = nums.size(), dp[n], l = 0, r = 0;

        dp[0] = nums[0];
        vector<int> queue(n + 1);
        queue[r++] = 0;
        for (int i = 1; i < n; ++i) {
            dp[i] = dp[queue[l]] + nums[i];
            // [l, r)
            while (l < r && dp[queue[r - 1]] < dp[i]) --r;
            queue[r++] = i;
            while (l < r && queue[l] < i - k + 1) ++l;
        }
        return dp[n - 1];
    }
};