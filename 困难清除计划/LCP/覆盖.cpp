// 插头DP
// 不知道爆搜能不能过掉
class Solution {
public:
    int domino(int n, int m, vector<vector<int>>& broken) {
        int dp[2][(1 << m)];
        memset(dp, 0, sizeof(dp));

        unordered_set<int> s;
        for (auto& p : broken) s.insert(p[0] * m + p[1]);

        int *cur, *next;
        cur = dp[0];
        next = dp[1];
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                for (int S = 0; S < (1 << m); ++S) {
                    if (s.count(i * m + j) || (S & (1 << j))) {
                        next[S] = cur[S & (~(1 << j))]; // 只能等于上一个状态确定的最大值
                    }
                    else {
                        int tmp = cur[S]; // 空着
                        if (j - 1 >= 0 && !s.count(i * m + j - 1) && !(S & (1 << (j - 1))))
                            tmp = max(tmp, cur[S | (1 << (j - 1))] + 1);  // 横放
                        if (i - 1 >= 0 && !s.count((i - 1) * m + j))
                            tmp = max(tmp, cur[S | (1 << j)] + 1); // 竖放
                        next[S] = tmp;
                    }
                }
                swap(next, cur);
            }
        }
        return cur[0];
    }
}; 