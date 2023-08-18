// https://leetcode.cn/problems/minimum-moves-to-move-a-box-to-their-target-location/



class Solution {
	int dis[20][20][20][20];
	static constexpr int dirs[4][2] = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
public:
    int minPushBox(vector<vector<char>>& grid) {
    	// 最短路径，通常是bfs搜索
    	// 状态的定义： 箱子的位置+人的位置
    	int n = grid.size(), m = grid[0].size(), ans = INT_MAX;
    	int tx, ty, sx, sy, bx, by;
    	for (int i = 0; i < n; ++i)
    		for (int j = 0; j < m; ++j) {
    			if (grid[i][j] == 'S') sx = i, sy = j;
    			if (grid[i][j] == 'T') tx = i, ty = j;
    			if (grid[i][j] == 'B') bx = i, by = j;
    		}
    	memset(dis, 0x3f, sizeof(dis));
    	queue<tuple<int, int, int, int>> q;
    	q.emplace(bx, by, sx, sy);
    	dis[bx][by][sx][sy] = 0;
    	while (!q.empty()) {
    		auto [x1, y1, x, y] = q.front();
    		q.pop();
    		if (x1 == tx && y1 == ty) ans = min(ans, dis[x1][y1][x][y]);
    		for (int k = 0; k < 4; ++k) {
    			int nx = x + dirs[k][0], ny = y + dirs[k][1];
    			if (nx < 0 || ny < 0 || nx >= n || ny >= m || grid[nx][ny] == '#') continue;
    			// 如果到达了箱子的位置，那么表明箱子也需要做相同的变换
    			if (nx == x1 && ny == y1) {
    				int x2 = x1 + dirs[k][0], y2 = y1 + dirs[k][1];
    				if (x2 < 0 || y2 < 0 || x2 >= n || y2 >= m || grid[nx][ny] == '#') continue; // 箱子动不了，所以人也动不了
    				if (dis[x2][y2][nx][ny] > dis[x1][y1][x][y] + 1) {
    					dis[x2][y2][nx][ny] = dis[x1][y1][x][y] + 1;
    					q.emplace(x2, y2, nx, ny);
    				}
    			}
    			else {
    				if (dis[x1][y1][nx][ny] > dis[x1][y1][x][y]) {
    					dis[x1][y1][nx][ny] = dis[x1][y1][x][y];
    					q.emplace(x1, y1, nx, ny);
    				}
    			}
    		}
    	}
    	return (ans == INT_MAX ? -1 : ans);
    }
};