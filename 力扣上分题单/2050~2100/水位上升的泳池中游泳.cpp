// https://leetcode.cn/problems/swim-in-rising-water/description/



class Solution {
public:
    int swimInWater(vector<vector<int>>& grid) {
    	int n = grid.size(), m = grid[0].size();
    	int mx = INT_MIN, mn = INT_MAX;

    	vector<int> dx{-1, 1, 0, 0};
    	vector<int> dy{0, 0, 1, -1};

    	for (auto c : grid)
    		for (auto p : c) {
    			mx = max(mx, p);
    			mn = min(mn, p);
    		}

    	vector vis(n, vector<bool>(m, false));
    	auto f = [&](int v) -> bool {
    		vector tmp(n, vector<int>(m));
    		for (int i = 0; i < n; ++i) {
    			for (int j = 0; j < m; ++j) {
    				vis[i][j] = false;
    				if (grid[i][j] <= v) tmp[i][j] = 0;
    				else tmp[i][j] = 1;
    			}
    		}
    		queue<pair<int, int>> q;
    		q.emplace(0, 0);
    		vis[0][0] = false;
    		while (!q.empty()) {
    			auto [x, y] = q.front();
    			q.pop();
    			if (x == n - 1 && y == m - 1) return true;
    			for (int i = 0; i < 4; ++i) {
    				int nx = x + dx[i], ny = y + dy[i];
    				if (nx < 0 || ny < 0 || nx >= n || ny >= m) continue;
    				if (!vis[nx][ny] && !tmp[nx][ny]) {
    					vis[nx][ny] = true;
    					q.emplace(nx, ny);
    				}
    			}
    		}
    		return false;
    	};

    	int l = max(mn, grid[0][0]), r = mx, ans;
    	while (l <= r) {
    		int mid = (l + r) >> 1;
    		if (f(mid)) ans = mid, r = mid - 1;
    		else l = mid + 1;
    	}

    	return ans;
    }
};