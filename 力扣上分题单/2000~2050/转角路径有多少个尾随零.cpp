// https://leetcode.cn/problems/maximum-trailing-zeros-in-a-cornered-path/
// 答案就是路径上2和5因子总数的较小值，并且可以发现数字越多越好，所以起点和终点应该都在边界上，枚举即可


int c25[1001][2];
int init = []() {
    for (int i = 2; i <= 1000; ++i) { // 预处理：递推算出每个数的因子 2 的个数和因子 5 的个数
        if (i % 2 == 0) c25[i][0] = c25[i / 2][0] + 1;
        if (i % 5 == 0) c25[i][1] = c25[i / 5][1] + 1;
    }
    return 0;
}();

class Solution {
public:
    int maxTrailingZeros(vector<vector<int>> &grid) {
        int m = grid.size(), n = grid[0].size(), ans = 0;
        int s[m][n + 1][2];
        for (int i = 0; i < m; ++i) {
            s[i][0][0] = s[i][0][1] = 0;
            for (int j = 0; j < n; ++j) {
                s[i][j + 1][0] = s[i][j][0] + c25[grid[i][j]][0]; // 每行的因子 2 的前缀和
                s[i][j + 1][1] = s[i][j][1] + c25[grid[i][j]][1]; // 每行的因子 5 的前缀和
            }
        }

        for (int j = 0; j < n; ++j) {
            for (int i = 0, s2 = 0, s5 = 0; i < m; ++i) { // 从上往下，枚举左拐还是右拐
                s2 += c25[grid[i][j]][0];
                s5 += c25[grid[i][j]][1];
                ans = max(ans, max(min(s2 + s[i][j][0], s5 + s[i][j][1]),
                                   min(s2 + s[i][n][0] - s[i][j + 1][0], s5 + s[i][n][1] - s[i][j + 1][1])));
            }
            for (int i = m - 1, s2 = 0, s5 = 0; i >= 0; --i) { // 从下往上，枚举左拐还是右拐
                s2 += c25[grid[i][j]][0];
                s5 += c25[grid[i][j]][1];
                ans = max(ans, max(min(s2 + s[i][j][0], s5 + s[i][j][1]),
                                   min(s2 + s[i][n][0] - s[i][j + 1][0], s5 + s[i][n][1] - s[i][j + 1][1])));
            }
        }
        return ans;
    }
};



