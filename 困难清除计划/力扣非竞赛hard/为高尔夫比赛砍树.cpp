class Solution {
    static constexpr int dirs[4][2] = {{0, -1}, {0, 1}, {1, 0}, {-1, 0}};
public:
    int cutOffTree(vector<vector<int>>& forest) {
        // 砍树的顺序是固定的

        // position, now at the chain postion
        int n = forest.size(), m = forest[0].size(), dp[n][m][n * m + 1];
        memset(dp, 0x3f, sizeof(dp));

        // 获取排名信息
        unordered_map<int, int> rank;
        vector<int> arr;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                if (forest[i][j] > 1) arr.push_back(forest[i][j]);
        sort(arr.begin(), arr.end());
        for (int i = 0; i < arr.size(); ++i) rank[arr[i]] = i + 1;

        // bfs 最短路算法
        // 朴素的算法会超时
        int start = (rank[forest[0][0]] > 1 ? 0 : rank[forest[0][0]]);
        dp[0][0][start] = 0;
        queue<tuple<int, int, int>> q;
        q.emplace(0, 0, start);
        while (!q.empty()) {
            auto [x, y, z] = q.front();
            q.pop();
            if (z == arr.size()) return dp[x][y][z];
            for (int i = 0; i < 4; ++i) {
                int nx = x + dirs[i][0], ny = y + dirs[i][1];
                if (nx < 0 || ny < 0 || nx >= n || ny >= m || forest[nx][ny] == 0) continue;
                int nxt = (forest[nx][ny] == arr[z] ? z + 1 : z);
                if (dp[nx][ny][nxt] == 0x3f3f3f3f) {
                    dp[nx][ny][nxt] = dp[x][y][z] + 1;
                    q.emplace(nx, ny, nxt);
                }
            }
        }
        return -1;
    }
};



// 实际上是一个贪心的算法
// 行走的路是固定的所有每一段求解一次最短路就可以了，但是复杂度和动态规是一样的。
// 唯一的差别在于贪心算法可能使用的空间复杂度比较低
// 但是力扣的数据测试样例设计不合理，同样复杂度的代码有些是过不去的。


