// https://leetcode.cn/problems/minimum-cost-to-split-an-array/submissions/396651530/
// 技巧：设置以某个字符结尾的状态下的最小代价


class Solution {
public:
    int minCost(vector<int>& nums, int k) {
        // dp
        int n = nums.size();
        long long res[1010][1010];
        long long cnt[1010];
        for (int i = 1; i <= n; i++) {
            memset(cnt, 0, sizeof(cnt));
            int temp = 0;
            for (int j = i; j <= n; ++j) {
                ++cnt[nums[j - 1]];
                if (cnt[nums[j - 1]] == 1) ++temp;
                else if (cnt[nums[j - 1]] == 2) --temp;
                res[i][j] = temp;
            }
        }
        int dp[1010];
        memset(dp, 0x3f, sizeof(dp));
        dp[0] = 0;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= i; ++j) {
                // j....i is a subarray
                int cost = k + (i - j + 1) - res[j][i];
                dp[i] = min(dp[j - 1] + cost, dp[i]);
            }
        }
        return dp[n];
    }
};