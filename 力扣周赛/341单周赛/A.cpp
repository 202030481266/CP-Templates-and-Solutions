class Solution {
public:
    vector<int> rowAndMaximumOnes(vector<vector<int>>& mat) {
        int mx = -1, res = -1, tmp = 0, n = mat.size(), m = mat[0].size();
        for (int i = 0; i < n; ++i) {
            tmp = 0;
            for (int j = 0; j < m; ++j) tmp += mat[i][j];
            if (tmp > mx) mx = tmp, res = i;
        }
        return {res, mx};
    }
};