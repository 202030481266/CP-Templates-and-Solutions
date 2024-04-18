const int dirs[4][2] = {{-1, 0}, {0, 1}, {0, -1}, {1, 0}};
class Solution {
public:
    vector<vector<int>> resultGrid(vector<vector<int>>& image, int threshold) {
        int n = image.size(), m = image[0].size();
        vector ans(n, vector<int>(m));
        vector cnt(n, vector<int>(m));

        auto check = [&](int x, int y) -> bool {
            for (int i = x; i <= x + 2; ++i)
                for (int j = y; j <= y + 2; ++j)
                    for (int k = 0; k < 4; ++k) {
                        int nx = i + dirs[k][0], ny = j + dirs[k][1];
                        if (nx >= x && ny >= y && nx <= x + 2 && ny <= y + 2) { 
                            // 这里思维定式非常容易出错，上下界一定要标清楚
                            if (abs(image[nx][ny] - image[i][j]) > threshold) {
                                return false;
                            }
                        }
                    }
            return true;
        };

        auto avg = [&](int x, int y) -> void {
            int sum = 0;
            for (int i = x; i <= x + 2; ++i)
                for (int j = y; j <= y + 2; ++j) 
                    sum += image[i][j];
            for (int i = x; i <= x + 2; ++i)
                for (int j = y; j <= y + 2; ++j)
                    ans[i][j] += sum / 9, ++cnt[i][j];
        };

        // 枚举区域
        for (int i = 0; i + 2 < n; ++i)
            for (int j = 0; j + 2 < m; ++j) 
                if (check(i, j)) 
                    avg(i, j);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                ans[i][j] = (cnt[i][j] > 0 ? ans[i][j] / cnt[i][j] : image[i][j]);
        return ans;
    }
};
