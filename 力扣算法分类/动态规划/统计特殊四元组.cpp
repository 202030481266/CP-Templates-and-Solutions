// https://leetcode.cn/problems/count-special-quadruplets/
// 注意答案统计的时候要枚举最后一个断点


class Solution {
public:
    int countQuadruplets(vector<int>& nums) {
        int n = nums.size();
        int s = accumulate(nums.begin(), nums.end(), 0);
        int mx = *max_element(nums.begin(), nums.end());

        vector dp(n + 1, vector(5, vector<int>(110)));
        dp[0][0][0] = 1;
        for (int i = 1; i <= n; ++i) {
            for (int j = 0; j <= 4; ++j) {
                for (int k = 0; k <= 100; ++k) {
                    dp[i][j][k] = dp[i - 1][j][k];
                    if (j >= 1 && k >= nums[i - 1])
                        dp[i][j][k] += dp[i - 1][j - 1][k - nums[i - 1]];
                }
            }
        }
        int ans = 0;
        for (int i = 3; i <= n - 1; ++i)
            ans += dp[i][3][nums[i]];
        return ans;
    }
};