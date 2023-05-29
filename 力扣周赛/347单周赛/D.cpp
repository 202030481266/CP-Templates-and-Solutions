class Solution {
    typedef tuple<int, int, int> tiii;
    typedef pair<int, int> pii;
public:
    int maxIncreasingCells(vector<vector<int>>& mat) {
        int n = mat.size(), m = mat[0].size(), dp[n][m], ans = 0;
        memset(dp, 0, sizeof(dp));
        vector<tiii> a;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j) a.emplace_back(mat[i][j], i, j);
        sort(a.begin(), a.end());
        map<int, int> row[n], col[m];
        set<int> r[n], c[m];
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j) r[i].emplace(mat[i][j]);
        for (int i = 0; i < m; ++i)
            for (int j = 0; j < n; ++j) c[i].emplace(mat[j][i]);
        for (int i = a.size() - 1; i >= 0; --i) {
            int x = get<1>(a[i]), y = get<2>(a[i]), v = get<0>(a[i]);
            auto it1 = r[x].upper_bound(v), it2 = c[y].upper_bound(v);
            if (it1 != r[x].end()) dp[x][y] = max(dp[x][y], row[x][*it1]);
            if (it2 != c[y].end()) dp[x][y] = max(dp[x][y], col[y][*it2]);
            dp[x][y] += 1;
            row[x][v] = max(row[x][v], dp[x][y]);
            col[y][v] = max(col[y][v], dp[x][y]);
            ans = max(ans, dp[x][y]);
        }
        return ans;
    }
};