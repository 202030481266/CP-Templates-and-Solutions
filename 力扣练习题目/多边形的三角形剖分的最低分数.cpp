class Solution {
public:
    int minScoreTriangulation(vector<int>& values) {
        // 区间dp
        int n = values.size();
        vector dp(n, vector<int>(n, -1));

        function<int(int, int)> dfs = [&](int x, int y) -> int {
            if (x + 1 == y) return 0;
            int &res = dp[x][y];

            if (res != -1) return res;
            res = INT_MAX;
            for (int i = x + 1; i < y; ++i)
                res = min(res, values[x] * values[y] * values[i] + dfs(x, i) + dfs(i, y));
            return res;
        };
        return dfs(0, n - 1);
    }
};