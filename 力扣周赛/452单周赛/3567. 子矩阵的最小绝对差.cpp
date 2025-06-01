// https://leetcode.cn/problems/minimum-absolute-difference-in-sliding-submatrix/description/
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;

static constexpr int inf = 0x3f3f3f3f;


class Solution {
public:
    vector<vector<int>> minAbsDiff(vector<vector<int>>& grid, int k) {
        int n = grid.size(), m = grid[0].size();
        vector ans(n - k + 1, vector<int>(m - k + 1, inf));
        vector<int> tmp;
        for (int i = 0; i < n - k + 1; ++i) {
            for (int j = 0; j < m - k + 1; ++j) {
                tmp.clear();
                for (int ii = i; ii < i + k; ++ii) {
                    for (int jj = j; jj < j + k; ++jj) {
                        tmp.push_back(grid[ii][jj]);
                    }
                }
                sort(tmp.begin(), tmp.end());
                tmp.erase(unique(tmp.begin(), tmp.end()), tmp.end());
                if (tmp.size() == 1) ans[i][j] = 0;
                else {
                    for (int ii = 0; ii < tmp.size() - 1; ++ii) {
                        ans[i][j] = min(ans[i][j], tmp[ii + 1] - tmp[ii]);
                    }
                }
            }
        }
        return ans;
    }
};