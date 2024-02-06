// 这道题主要必须要意识到一个重要的结论：单位等和子集 S 的情况最多并且最少使用 |S| - 1 次交易来调配
// 单位等和集合表示无法切割出任意的等和子集的集合
// 证明： https://leetcode.cn/circle/discuss/KcwT2s/ 第四题
class Solution {
public:
    int minTransfers(vector<vector<int>> &transactions) {
        const int n = 12, m = 1 << n;
        int cnt[n] = {};
        for (auto &d: transactions) {
            cnt[d[0]] -= d[2];
            cnt[d[1]] += d[2];
        }
        int f[m];
        f[0] = 0;
        for (int i = 1; i < m; ++i) {
            int sum = 0;
            for (int j = 0; j < n; ++j)
                if (i >> j & 1) sum += cnt[j];
            if (sum) f[i] = INT_MAX / 2; // 防止溢出
            else {
                f[i] = __builtin_popcount(i) - 1;
                for (int j = (i - 1) & i; j > 0; j = (j - 1) & i)
                    f[i] = min(f[i], f[j] + f[i ^ j]);
            }
        }
        return f[m - 1];
    }
};

