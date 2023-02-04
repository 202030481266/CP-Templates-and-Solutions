// 暴力标记法，搜一遍之后把路径撤掉
// 上下轮廓必须是两条没有交集的路径

class Solution {
public:
    bool isPossibleToCutPath(vector<vector<int>> &g) {
        int m = g.size(), n = g[0].size();

        // 下轮廓，优先向下，其次向右
        function<bool(int, int)> dfs1 = [&](int x, int y) -> bool { // 返回能否到达终点
            if (x == m - 1 && y == n - 1) return true;
            g[x][y] = 0; // 直接修改
            return x < m - 1 && g[x + 1][y] && dfs1(x + 1, y) ||
                   y < n - 1 && g[x][y + 1] && dfs1(x, y + 1);
        };

        // 上轮廓，优先向右，其次向下
        function<bool(int, int)> dfs2 = [&](int x, int y) -> bool { // 返回能否到达终点
            return x == m - 1 && y == n - 1 ||
                   x < m - 1 && g[x + 1][y] && dfs2(x + 1, y) ||
                   y < n - 1 && g[x][y + 1] && dfs2(x, y + 1);
        };

        // 提前特判一些可以直接得到答案的情况
        return m * n > 2 && (m == 1 || n == 1 || g[1][0] == 0 || g[0][1] == 0 || g[m - 2][n - 1] == 0 || g[m - 1][n - 2] == 0 ||
               !dfs1(1, 0) || !dfs2(0, 1));
    }
};

