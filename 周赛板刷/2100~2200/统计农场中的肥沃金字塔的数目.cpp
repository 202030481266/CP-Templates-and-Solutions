// https://leetcode.cn/problems/count-fertile-pyramids-in-a-land/
// 形状方案统计问题，和明显具有dp的性质，可以从网格DP问题入手


class Solution {
public:
    int countPyramids(vector<vector<int>>& grid) {
    	int m = grid.size(), n = grid[0].size();
    	vector f(m, vector<int>(n));

    	int ans = 0;
    	for (int i = m - 1; i >= 0; --i) {
    		for (int j = 0; j < n; ++j) {
    			if (grid[i][j] == 0) {
    				f[i][j] = -1;
    			}
    			else if (i == m - 1 || j == 0 || j == n - 1) {
    				f[i][j] = 0;
    			}
    			else {
    				f[i][j] = min({f[i + 1][j], f[i + 1][j - 1], f[i + 1][j + 1]}) + 1;
    				ans += f[i][j];
    			}
    		}
    	}
    	for (int i = 0; i < m; ++i) {
    		for (int j = 0; j < n; ++j) {
    			if (grid[i][j] == 0) {
    				f[i][j] = -1;
    			}
    			else if (i == 0 || j == 0 || j == n - 1) {
    				f[i][j] = 0;
    			}
    			else {
    				f[i][j] = min({f[i - 1][j], f[i - 1][j - 1], f[i - 1][j + 1]}) + 1;
    				ans += f[i][j];
    			}
    		}
    	}
    	return ans;
    }
};