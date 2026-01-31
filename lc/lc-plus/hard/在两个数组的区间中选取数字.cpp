const int mod = 1e9 + 7, N = 10000;
int dp[105][20010];

class Solution {
public:
    int countSubranges(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size();
        memset(dp, 0, sizeof(dp));

        vector<int> sum1(n + 1), sum2(n + 1);
        for (int i = 0; i < n; ++i) {
            sum1[i + 1] = sum1[i] + nums1[i];
            sum2[i + 1] = sum2[i] + nums2[i];
        }
        for (int i = 1; i <= n; ++i) {
            dp[i][N + nums1[i - 1]] += 1;
            dp[i][N - nums2[i - 1]] += 1;
            for (int j = -sum2[i]; j <= sum1[i]; ++j) {
                if (j + nums2[i - 1] <= N)
                    dp[i][j + N] = (dp[i][j + N] + dp[i - 1][j + nums2[i - 1] + N]) % mod;
                if (j - nums1[i - 1] >= -N)
                    dp[i][j + N] = (dp[i][j + N] + dp[i - 1][j - nums1[i - 1] + N]) % mod;
            }
        }
        int ans = 0;
        for (int i = 1; i <= n; ++i)
            ans = (ans + dp[i][N]) % mod;
        return ans;
    }
};