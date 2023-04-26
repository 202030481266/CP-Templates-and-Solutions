class Solution {
public:
    int maxSumTwoNoOverlap(vector<int>& nums, int firstLen, int secondLen) {
        int n = nums.size(), f[n + 2], g[n + 2], a[n + 2];
        memset(f, 0, sizeof(f));
        memset(g, 0, sizeof(g));
        for (int i = 1; i <= n; ++i) f[i] = f[i - 1] + nums[i - 1];
        for (int i = n - firstLen + 1; i >= 1; --i) {
            // [i, i + firstLen - 1]
            g[i] = max(g[i + 1], f[i + firstLen - 1] - f[i - 1]);
        }
        for (int i = n - secondLen + 1; i >= 1; --i) {
            // [i, i + secondLen - 1]
            a[i] = max(a[i + 1], f[i + secondLen - 1] - f[i - 1]);
        }
        int mx1 = 0, mx2 = 0, ans = 0;
        for (int i = 1; i + firstLen + secondLen - 1 <= n; ++i) {
            mx1 = max(mx1, f[i + firstLen - 1] - f[i - 1]);
            ans = max(ans, mx1 + a[i + firstLen]);
        }
        for (int i = 1; i + firstLen + secondLen - 1 <= n; ++i) {
            mx2 = max(mx2, f[i + secondLen - 1] - f[i - 1]);
            ans = max(ans, mx2 + g[i + secondLen]);
        }
        return ans;
    }
};