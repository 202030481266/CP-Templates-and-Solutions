class Solution {
public:
    int maximumsSplicedArray(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size(), dp[n + 1], f[n + 1], g[n + 1];
        memset(dp, 0, sizeof(dp));
        memset(f, 0, sizeof(f));
        memset(g, 0, sizeof(g));
        int ans = 0, s1 = 0, s2 = 0;
        for (int i = 0; i < n; ++i) {
            f[i] = nums2[i] - nums1[i];
            g[i] = nums1[i] - nums2[i];
            s1 += nums1[i];
            s2 += nums2[i];
        }
        ans = max(s1, s2);
        for (int i = 0; i < n; ++i) {
            dp[i] = f[i];
            if (i - 1 >= 0)
                dp[i] = max(dp[i - 1] + f[i], dp[i]);
            ans = max(ans, s1 + dp[i]);
        }
        memset(dp, 0, sizeof(dp));
        for (int i = 0; i < n; ++i) {
            dp[i] = g[i];
            if (i - 1 >= 0)
                dp[i] = max(dp[i - 1] + g[i], dp[i]);
            ans = max(ans, s2 + dp[i]);
        }
        return ans;
    }
};