class Solution {
    typedef pair<int, int> pii;
public:
    int firstCompleteIndex(vector<int>& arr, vector<vector<int>>& mat) {
        int N = arr.size(), n = mat.size(), m = mat[0].size(), row[n], col[m];
        memset(row, 0, sizeof(row));
        memset(col, 0, sizeof(col));
        vector<pii> tmp(n * m + 1);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                tmp[mat[i][j]] = pii{i, j};
        for (int i = 0; i < N; ++i) {
            auto [r, c] = tmp[arr[i]];
            ++row[r];
            ++col[c];
            if (row[r] == m || col[c] == n) return i;
        }
        return 0;
    }
};