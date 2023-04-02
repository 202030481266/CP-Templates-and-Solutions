// https://leetcode.cn/problems/minimum-score-triangulation-of-polygon/solutions/2203005/shi-pin-jiao-ni-yi-bu-bu-si-kao-dong-tai-aty6/
// 非常灵活的区间DP，需要转换


class Solution {
public:
    int minScoreTriangulation(vector<int> &v) {
        int n = v.size(), memo[n][n];
        memset(memo, -1, sizeof(memo)); // -1 表示还没有计算过
        function<int(int, int)> dfs = [&](int i, int j) -> int {
            if (i + 1 == j) return 0; // 只有两个点，无法组成三角形
            int &res = memo[i][j]; // 注意这里是引用，下面会直接修改 memo[i][j]
            if (res != -1) return res;
            res = INT_MAX;
            for (int k = i + 1; k < j; ++k) // 枚举顶点 k
                res = min(res, dfs(i, k) + dfs(k, j) + v[i] * v[j] * v[k]);
            return res;
        };
        return dfs(0, n - 1);
    }
};

