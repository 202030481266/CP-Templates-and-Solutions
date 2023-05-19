// https://leetcode.cn/problems/new-21-game/
// 前缀和优化+动态规划


class Solution {
public:
    double new21Game(int n, int k, int maxPts) {
        if (k == 0 || n >= k + maxPts - 1) return 1; // 特判
        vector<double> f(n + 1, 0), g(n + 1, 0);
        f[0] = g[0] = 1;
        for (int i = 1; i <= n; ++i) {
            int r = min(maxPts, i), l = max(1 + i - k, 1);
            if (r == i) f[i] = g[i - l] / maxPts;
            else f[i] = (g[i - l] - g[i - r - 1]) / maxPts;
            g[i] = g[i - 1] + f[i];
        }
        return g[n] - g[k - 1];
    }
};