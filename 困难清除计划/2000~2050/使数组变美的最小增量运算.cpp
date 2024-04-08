long long dp[2][3];
class Solution {
public:
    long long minIncrementOperations(vector<int>& nums, int k) {
        int n = nums.size();
        if (n <= 2) return 0;

        memset(dp, 0x3f, sizeof(dp));
        int pre = 0, cur = 1;
        for (int i = 0; i < 3; ++i)
            dp[pre][i] = max(0, k - nums[i]);
        for (int i = 4; i <= n; ++i) {
            dp[cur][2] = min(dp[pre][0], min(dp[pre][1], dp[pre][2])) + max(0, k - nums[i - 1]); 
            dp[cur][0] = dp[pre][1];
            dp[cur][1] = dp[pre][2];
            pre ^= 1;
            cur ^= 1;
        }

        return min(dp[pre][0], min(dp[pre][1], dp[pre][2]));
    }
};