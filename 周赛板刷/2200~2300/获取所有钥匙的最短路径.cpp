// https://leetcode.cn/problems/shortest-path-to-get-all-keys/



class Solution {
	typedef tuple<int, int, int> tiii;
	static constexpr int dirs[4][2] = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
public:
    int shortestPathAllKeys(vector<string>& grid) {
    	// 1 <= k <= 6，每一个钥匙都唯一对应一个锁
    	// 1 <= m, n <= 30
    	int n = grid.size(), m = grid[0].size(), dis[n][m][1 << 6]; 
    	int stx = -1, sty = -1, key = 0;
    	memset(dis, 0x3f, sizeof(dis));
    	queue<tiii> q;
    	for (int i = 0; i < n; ++i)
    		for (int j = 0; j < m; ++j) {
    			if (grid[i][j] == '@') stx = i, sty = j, grid[i][j] = '.';
    			if (islower(grid[i][j])) ++key;
    		}
    	dis[stx][sty][0] = 0;
    	q.emplace(stx, sty, 0);
    	while (!q.empty()) {
    		auto [x, y, d] = q.front();
    		q.pop();
    		if (d == ((1 << key) - 1)) return dis[x][y][d];
    		for (int i = 0; i < 4; ++i) {
    			int nx = x + dirs[i][0], ny = y + dirs[i][1];
    			if (nx < 0 || ny < 0 || nx >= n || ny >= m || grid[nx][ny] == '#') continue;
    			if (isupper(grid[nx][ny]) && ((d >> (grid[nx][ny] - 'A')) & 1) && dis[nx][ny][d] > dis[x][y][d] + 1) {
    				dis[nx][ny][d] = dis[x][y][d] + 1;
    				q.emplace(nx, ny, d);
    			}
    			if (islower(grid[nx][ny]) && dis[nx][ny][d | (1 << (grid[nx][ny] - 'a'))] > dis[x][y][d] + 1) {
    				dis[nx][ny][d | (1 << (grid[nx][ny] - 'a'))] = dis[x][y][d] + 1;
    				q.emplace(nx, ny, d | (1 << (grid[nx][ny] - 'a')));
    			}
    			if (grid[nx][ny] == '.' && dis[nx][ny][d] > dis[x][y][d] + 1) {
    				dis[nx][ny][d] = dis[x][y][d] + 1;
    				q.emplace(nx, ny, d);
    			}
    		}
    	}
    	return -1;
    }
};