class Solution {
public:
    int maxProduct(string s) {
        int n = s.size(), dp[1<<n];
        memset(dp, 0, sizeof(dp));
        for (int i = 1; i < (1 << n); ++i) {
            int l = 0, r = n - 1;
            while (l < n && !((i >> l) & 1)) ++l;
            while (r >= 0 && !((i >> r) & 1)) --r;
            bool flag = true;
            while (l < r) {
                if (s[l] != s[r]) {
                    flag = false;
                    break;
                }
                ++l;
                --r;
                while (l < n && !((i >> l) & 1)) ++l;
                while (r >= 0 && !((i >> r) & 1)) --r;
            }
            if (flag) dp[i] = __builtin_popcount(i);
        }
        int mx[1<<n];
        memset(mx, 0, sizeof(mx));
        for (int i = (1 << n) - 1; i >= 1; --i) {
            for (int j = i; j; j = (j - 1) & i) {
                mx[i] = max(mx[i], dp[j]);
            }
        }
        int ans = 0;
        for (int i = 1; i < (1 << n); ++i) {
            if (dp[i])
                ans = max(ans, dp[i] * mx[(1 << n) - 1 - i]);
        }
        return ans;
    }
};