// 区间DP
class Solution {
public:
    int maxDotProduct(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size(), m = nums2.size(), f[n + 1][m + 1];
        memset(f, -0x3f, sizeof(f));

        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j) {
                int tmp;
                if (i - 1 <= 0 || j - 1 <= 0) {
                    tmp = nums2[j - 1] * nums1[i - 1];
                }
                else tmp = nums2[j - 1] * nums1[i - 1] + (f[i - 1][j - 1] > 0 ? f[i - 1][j - 1] : 0);
                f[i][j] = tmp;
                if (i - 1 > 0) f[i][j] = max(f[i - 1][j], f[i][j]);
                if (j - 1 > 0) f[i][j] = max(f[i][j], f[i][j - 1]);
            }

        return f[n][m];
    }
};