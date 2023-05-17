// https://leetcode.cn/problems/escape-the-spreading-fire/



class Solution {
	typedef pair<int, int> pii;
	typedef tuple<int, int, int> tiii;
	static constexpr int dirs[4][2] = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
public:
    int maximumMinutes(vector<vector<int>>& grid) {
    	int n = grid.size(), m = grid[0].size(), time[n][m], vis[n][m];
    	memset(time, 0x3f, sizeof(time));
    	vector<pii> q;
    	for (int i = 0; i < n; ++i)
    		for (int j = 0; j < m; ++j)
    			if (grid[i][j] == 1) q.emplace_back(i, j);
    	for (int d = 0; !q.empty(); ++d) {
    		vector<pii> tmp;
    		for (int i = 0; i < q.size(); ++i) {
    			int x = q[i].first, y = q[i].second;
    			time[x][y] = d;
    			for (int k = 0; k < 4; ++k) {
    				int nx = x + dirs[k][0], ny = y + dirs[k][1];
    				if (nx < 0 || ny < 0 || nx >= n || ny >= m || grid[nx][ny] == 2) continue;
    				if (time[nx][ny] > d + 1) {
    					tmp.emplace_back(nx, ny);
    				}
    			}
    		}
    		q = move(tmp);
    	}
    	auto check = [&](int T) -> bool {
    		if (time[0][0] <= T) return false; // 起点已经着火了
    		memset(vis, 0, sizeof(vis));
    		queue<tiii> q;
    		q.emplace(0, 0, T);
    		vis[0][0] = 1;
    		while (!q.empty()) {
    			auto [x, y, t] = q.front();
    			q.pop();
    			if (x == n - 1 && y == m - 1) return true;
    			for (int k = 0; k < 4; ++k) {
    				int nx = x + dirs[k][0], ny = y + dirs[k][1];
    				if (nx < 0 || ny < 0 || nx >= n || ny >= m || grid[nx][ny] == 2) continue; 
    				if (!vis[nx][ny] && ((time[nx][ny] == t + 1 && nx == n - 1 && ny == m - 1) || time[nx][ny] > t + 1)) {
    					vis[nx][ny] = 1;
    					q.emplace(nx, ny, t + 1);
    				}
    			}
    		}
    		return false;
    	}; 
    	int l = 0, r = 1e9, ans = -1;
    	while (l <= r) {
    		int mid = (l + r) >> 1;
    		if (check(mid)) ans = mid, l = mid + 1;
    		else r = mid - 1;
    	}
    	return ans;
    }
};