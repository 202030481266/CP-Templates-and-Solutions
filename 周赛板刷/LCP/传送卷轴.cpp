// we must shorten the path after transfered but not the no-transfered path
class Solution {
	using pii = pair<int, int>;
	static constexpr int dirs[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
public:
    int challengeOfTheKeeper(vector<string>& maze) {
		int n = maze.size(), m = maze[0].size(), dis[n][m], val[n][m], dp[n][m];
		memset(val, 0, sizeof(val));
		memset(dis, 0x3f, sizeof(dis));
		memset(dp, 0x3f, sizeof(dp));

		// the start position and end position
		int sx, sy, tx, ty;

		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				if (maze[i][j] == 'T') 
					tx = i, ty = j;
				if (maze[i][j] == 'S')
					sx = i, sy = j;
			}
		}
		queue<pair<int, int>> q;
		q.emplace(tx, ty);
		dis[tx][ty] = 0;
		// calculate the shortest path from T to any other place
		while (!q.empty()) {
			auto [x, y] = q.front();
			q.pop();
			for (int i = 0; i < 4; ++i) {
				int nx = x + dirs[i][0], ny = y + dirs[i][1];
				if (nx >= 0 && ny >= 0 && nx < n && ny < m && maze[nx][ny] != '#') {
					if (dis[nx][ny] > dis[x][y] + 1) {
						dis[nx][ny] = dis[x][y] + 1;
						q.emplace(nx, ny);
					}
				}
			}
		}
		// so the path should be transfered
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				if (maze[i][j] != '.') continue;
				// maze[i][j] is space
				// vertical 
				if (maze[i][m - 1 - j] != '#') val[i][j] = max(val[i][j], dis[i][m - 1 - j]);
				// horizontal
				if (maze[n - 1 - i][j] != '#') val[i][j] = max(val[i][j], dis[n - 1 - i][j]);
			}
		}
		priority_queue<pii, vector<pii>, greater<pii>> pq;
		pq.emplace(0, tx * m + ty);
		dp[tx][ty] = 0;
		while (!pq.empty()) {
			auto [c, u] = pq.top();
			pq.pop();
			int x = u / m, y = u % m;
			if (dp[x][y] != c) continue;
			for (int i = 0; i < 4; ++i) {
				int nx = x + dirs[i][0], ny = y + dirs[i][1];
				if (nx >= 0 && ny >= 0 && nx < n && ny < m && maze[nx][ny] != '#') {
					if (dp[nx][ny] > max(val[nx][ny], c)) {
						dp[nx][ny] = max(val[nx][ny], c);
						pq.emplace(dp[nx][ny], nx * m + ny);
					}
				}
			}
		}
		return (dp[sx][sy] == 0x3f3f3f3f ? -1 : dp[sx][sy]); 
	}
};
