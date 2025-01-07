// 动态规划，非常困难
class Solution {
public:
    int removeBoxes(vector<int>& boxes) {
        // 假设只有两种数字 0 1 

        int n = boxes.size(), dp[n][n][n];
        memset(dp, -1, sizeof(dp));

        function<int(int, int, int)> dfs = [&](int i, int j, int k) -> int {
            if (i > j) return 0;
            if (dp[i][j][k] != -1) return dp[i][j][k];
            int& res = dp[i][j][k];
            // 贪心选择的性质，合并在一起消除总是更加好的选择（因为取得是平方和）
            while (i + 1 <= j && boxes[i + 1] == boxes[i]) ++i, ++k; // should remove forward if the left is the same character
            res = (k + 1) * (k + 1) + dfs(i + 1, j, 0);
            for (int m = i + 1; m <= j; ++m)
                if (boxes[m] == boxes[i]) res = max(res, dfs(i + 1, m - 1, 0) + dfs(m, j, k + 1));
        };
        return dfs(0, n - 1, 0);
    }
};