// https://leetcode.cn/problems/shortest-path-in-a-grid-with-obstacles-elimination/
// bfs + 状态最短路


class Solution {
public:
    int shortestPath(vector<vector<int>>& grid, int k) {
    	int n = grid.size();
    	int m = grid[0].size();
    	vector dp(n + 1, vector(m + 1, vector<int>(k + 1, -1)));
    	vector<int> dx{-1, 1, 0, 0};
    	vector<int> dy{0, 0, -1, 1};

    	auto f = [&](int x, int y) {
    		return (x >= 0) && (x < n) && (y < m) && (y >= 0);
    	};
        int ans = INT_MAX;
    	dp[n - 1][m - 1][k] = 0;
    	queue<tuple<int, int, int>> q;
    	q.push(make_tuple(n - 1, m - 1, k));
    	while (!q.empty()) {
    		auto cur = q.front();
    		q.pop();
    		int x = get<0>(cur), y = get<1>(cur), w = get<2>(cur);
            if (x == 0 && y == 0) ans = min(ans, dp[x][y][w]);
    		for (int i = 0; i < 4; ++i) {
    			int nx = x + dx[i], ny = y + dy[i];
    			if (f(nx, ny)) {
    				if (grid[nx][ny] && w > 0 && dp[nx][ny][w - 1] == -1) {
    					dp[nx][ny][w - 1] = dp[x][y][w] + 1;
    					q.push(make_tuple(nx, ny, w - 1));
    				}
    				if (!grid[nx][ny] && dp[nx][ny][w] == -1) {
    					dp[nx][ny][w] = dp[x][y][w] + 1;
    					q.push(make_tuple(nx, ny, w));
    				}
    			}
    		}
    	}
    	return ans == INT_MAX ? -1 : ans;
    }
};