// xiaoshulin
// 2023.12.11
class Solution {
	using pii = pair<int, int>;
	static constexpr int dirs[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
public:
    int minimumEffortPath(vector<vector<int>>& heights) {
		int n = heights.size(), m = heights[0].size(), dis[n * m];
		memset(dis, 0x3f, sizeof(dis));

		// dijkstra 
		// dis[v] = min(max(dp[u], abs(u - v))) = max(min(dp[u]), abs(u - v))

		priority_queue<pii, vector<pii>, greater<pii>> q;
		q.emplace(0, 0);
		dis[0] = 0;
		while (!q.empty()) {
			auto [c, u] = q.top();
			q.pop();
			if (c != dis[u]) continue;
			int x = u / m, y = u % m;
			for (int i = 0; i < 4; ++i) {
				int nx = x + dirs[i][0], ny = y + dirs[i][1];
				if (nx >= 0 && ny >= 0 && nx < n && ny < m) {
					if (dis[nx * m + ny] > max(c, abs(heights[x][y] - heights[nx][ny]))) {
						dis[nx * m + ny] = max(c, abs(heights[x][y] - heights[nx][ny]));
						q.emplace(dis[nx * m + ny], nx * m + ny);
					}
				}
			}
		}
		return dis[n * m - 1];
    }
};
