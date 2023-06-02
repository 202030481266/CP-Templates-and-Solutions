class Solution {
    typedef long long ll;
public:
    long long sellingWood(int m, int n, vector<vector<int>>& prices) {
        ll dp[m + 1][n + 1], val[m + 1][n + 1];
        memset(dp, -1, sizeof(dp));
        memset(val, 0, sizeof(val));
        for (auto &c : prices) val[c[0]][c[1]] = c[2];
        function<ll(int, int)> dfs = [&](int h, int w) -> ll {
            if (h == 0 || w == 0) return 0;
            ll& res = dp[h][w];
            if (res != -1) return res;
            res = val[h][w];
            // 垂直分割, [1...i] 是左边
            for (int i = 1; i <= w; ++i) 
                res = max(res, dfs(h, i) + dfs(h, w - i));
            // 水平分割, [1.. i]是上面
            for (int i = 1; i <= h; ++i)
                res = max(res, dfs(i, w) + dfs(h - i, w));
            return res;
        };
        return dfs(m, n);
    }
};