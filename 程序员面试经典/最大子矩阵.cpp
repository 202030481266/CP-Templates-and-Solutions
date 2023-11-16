class Solution {
public:
    vector<int> getMaxMatrix(vector<vector<int>>& matrix) {
        // 枚举矩形的左上角端点和右下角的端点显然不现实
        // 枚举三个维度是可以接受的，剩下的一个维度必然要O(1)常数求解

        int n = matrix.size(), m = matrix[0].size(), sum[m + 1][n + 1];
        memset(sum, 0, sizeof(sum));

        for (int i = 0; i < m; ++i) 
            for (int j = 0; j < n; ++j) sum[i][j + 1] = sum[i][j] + matrix[j][i];

        int ans = INT_MIN;  
        int l_x, l_y, r_x, r_y;
        for (int i = 0; i < n; ++i) {
            for (int j = i; j < n; ++j) {
                int mn = 0, s = 0, idx = -1;
                for (int k = 0; k < m; ++k) {
                    // [i, j]
                    int tmp = sum[k][j + 1] - sum[k][i];
                    s += tmp;
                    if (s - mn > ans) {
                        ans = s - mn;
                        l_x = i;
                        l_y = idx + 1;
                        r_x = j;
                        r_y = k;
                    }
                    if (s < mn) {
                        mn = s;
                        idx = k;
                    }
                }
            }
        }

        return {l_x, l_y, r_x, r_y};
    }
};