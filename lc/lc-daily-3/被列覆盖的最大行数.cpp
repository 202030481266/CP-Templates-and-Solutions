class Solution {
public:
    int maximumRows(vector<vector<int>>& matrix, int numSelect) {
        int n = matrix.size(), m = matrix[0].size();

        vector<int> row(n);
        for (int i = 0; i < n; ++i) {
            int& r = row[i];
            for (int j = 0; j < m; ++j) {
                if (matrix[i][j] & 1)
                    r |= (1 << j);
            }
        }

        int ans = 0; 
        for (int i = 0; i < (1 << n); ++i) {
            int s = 0, c = 0;
            for (int j = 0; j < n; ++j) {
                if ((i >> j) & 1) 
                    s |= row[j], ++c;
            }
            if (__builtin_popcount(s) <= numSelect) ans = max(ans, c);
        }
        return ans;
    }
};