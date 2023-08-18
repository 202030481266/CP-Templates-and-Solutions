class Solution {
public:
    int getMaxGridHappiness(int m, int n, int introvertsCount, int extrovertsCount) {
        int mask_max = 1;
        for (int i = 0; i < n; ++i) mask_max *= 3;
        int dp[m + 1][mask_max][introvertsCount + 1][extrovertsCount + 1];
        int f[mask_max][mask_max];
        memset(f, 0, sizeof(f));
        memset(dp, -1, sizeof(dp));
        for (int i = 0; i < mask_max; ++i) {
            vector<int> a;
            for (int k = 0, w = i; k < n; ++k, w /= 3) a.push_back(w % 3);
            for (int j = 0; j < mask_max; ++j) {
                vector<int> b;
                for (int k = 0, w = j; k < n; ++k, w /= 3) b.push_back(w % 3);
                int& res = f[i][j];
                // 先计算 b 的得分
                for (int k = 0; k < n; ++k) {
                    if (b[k] == 1) {
                        f[i][j] += 120;
                        if (a[k]) f[i][j] -= 30;
                        if (k + 1 < n && b[k + 1]) f[i][j] -= 30;
                        if (k - 1 >= 0 && b[k - 1]) f[i][j] -= 30;
                    }
                    if (b[k] == 2) {
                        f[i][j] += 40;
                        if (a[k]) f[i][j] += 20;
                        if (k + 1 < n && b[k + 1]) f[i][j] += 20;
                        if (k - 1 >= 0 && b[k - 1]) f[i][j] += 20;
                    }
                }
                // 计算 a 的变化分数
                for (int k = 0; k < n; ++k) {
                    if (a[k] == 1 && b[k]) f[i][j] -= 30;
                    if (a[k] == 2 && b[k]) f[i][j] += 20;
                }
            }
        }
        dp[0][0][0][0] = 0;
        for (int i = 1; i <= m; ++i) {
            for (int in = 0; in <= introvertsCount; ++in) {
                for (int out = 0; out <= extrovertsCount; ++out) {
                    for (int j = 0; j < mask_max; ++j) {
                        int cnt1 = 0, cnt2 = 0;
                        for (int k = 0, dummy = j; k < n; ++k, dummy /= 3) {
                            if (dummy % 3 == 1) ++cnt1;
                            if (dummy % 3 == 2) ++cnt2;
                        }
                        if (cnt1 > in || cnt2 > out) continue;
                        for (int mask = 0; mask < mask_max; ++mask) {
                            int tmp = dp[i - 1][mask][in - cnt1][out - cnt2];
                            if (tmp != -1)
                                dp[i][j][in][out] = max(dp[i][j][in][out], tmp + f[mask][j]);
                        }
                    }
                }
            }
        }
        int ans = 0;
        for (int i = 0; i < mask_max; ++i)
            for (int in = 0; in <= introvertsCount; ++in)
                for (int out = 0; out <= extrovertsCount; ++out)
                    ans = max(ans, dp[m][i][in][out]);
        return ans;
    }
};