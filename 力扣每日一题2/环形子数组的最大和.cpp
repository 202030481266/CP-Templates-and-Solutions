class Solution {
public:
    int maxSubarraySumCircular(vector<int>& nums) {
        // 最大子数组和
        int n = nums.size(), dp[n + 1], ans = INT_MIN;
        memset(dp, 0, sizeof(dp));
        for (int i = 1; i <= n; ++i) {
            if (dp[i - 1] > 0) dp[i] = dp[i - 1] + nums[i - 1];
            else dp[i] = nums[i - 1];
            ans = max(ans, dp[i]);
        }
        vector<int> pre(n + 1), mx(n + 1);
        for (int i = 1; i <= n; ++i) {
            pre[i] = pre[i - 1] + nums[i - 1];
            mx[i] = max(pre[i], mx[i - 1]);
        }
        int st = 0;
        for (int i = n; i >= 1; --i) {
            st += nums[i - 1];
            ans = max(ans, mx[i - 1] + st);
        }
        return ans;
    }
};