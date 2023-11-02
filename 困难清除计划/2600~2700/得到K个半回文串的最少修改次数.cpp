class Solution {
public:
    int minimumChanges(string s, int k) {
        int n = s.size(), f[n + 1][n + 1], dp[n + 1][k + 1];

        // 无论什么字符串，一定可以修改，最大的代价就是全部变成同一个字母
        memset(f, 0x3f, sizeof(f));
        memset(dp, 0x3f, sizeof(dp));

        // 计算最小代价的函数
        auto cal = [&](int left, int right, int d) -> int {
            int g = (right - left + 1) / d, sum = 0;
            for (int i = 0; i < d; ++i) {
                int l = left + i, r = l + (g - 1) * d;
                while (l < r) {
                    if (s[l] != s[r]) ++sum;
                    l += d;
                    r -= d;
                }
            }
            return sum;
        };

        // 计算最小代价
        for (int i = 0; i < n; ++i) {
            for (int j = i; j < n; ++j) {
                // 枚举长度
                int len = j - i + 1, tmp = INT_MAX;
                for (int d = 1; d * d <= len; ++d) {
                    if (len % d == 0) {
                        tmp = min(tmp, cal(i, j, d));
                        if (d != 1 && d != len / d) {
                            tmp = min(tmp, cal(i, j, len / d));
                        }
                    }
                }
                f[i + 1][j + 1] = f[j + 1][i + 1] = tmp;
            }
            
        }

        // DP
        // 长度必须为2或者以上才行
        dp[0][0] = 0;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= min(i, k); ++j) {
                for (int x = j; x < i; ++x) {
                    if (dp[x - 1][j - 1] != 0x3f3f3f3f)
                        dp[i][j] = min(dp[i][j], dp[x - 1][j - 1] + f[x][i]);
                }
            }
        }
        return dp[n][k];
    }
};