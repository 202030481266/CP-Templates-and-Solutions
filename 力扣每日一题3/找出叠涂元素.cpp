class Solution {
public:
    int firstCompleteIndex(vector<int>& arr, vector<vector<int>>& mat) {
        int n = mat.size(), m = mat[0].size();

        vector<int> row(n), col(m);

        unordered_map<int, int> pos;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                pos[mat[i][j]] = i * m + j;
        for (int i = 0; i < n * m; ++i) {
            int x = pos[arr[i]] / m, y = pos[arr[i]] % m;
            row[x]++, col[y]++;
            if (row[x] == m || col[y] == n) return i;
        }
        return -1;
    }
};