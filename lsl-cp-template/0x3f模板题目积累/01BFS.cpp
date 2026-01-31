// 题目模板： https://leetcode.cn/problems/minimum-obstacle-removal-to-reach-corner/
// 适用于边权为0，1的图的最短路径快速搜索

/*
	1、bfs的队列要满足二段性
	2、遇到边权为0的边，实际上就是在bfs树的同一层，那么直接放到队列头部，如果是边权为1放到队列尾部
*/


class Solution {
public:
    int minimumObstacles(vector<vector<int>>& grid) {
    	int n = grid.size(), m = grid[0].size();

    	vector<int> dx{-1, 1, 0, 0};
    	vector<int> dy{0, 0, 1, -1};
    	vector dis(n, vector<int>(m, 0x3f3f3f3f));
    	dis[0][0] = 0;

    	deque<pair<int, int>> q;
		q.emplace_front(0, 0);
    	while (!q.empty()) {
    		auto [x, y] = q.front();
    		q.pop_front();
    		for (int k = 0; k < 4; ++k) {
    			int nx = x + dx[k], ny = y + dy[k];
    			if (nx < 0 || ny < 0 || nx >= n || ny >= m) continue;
    			if (grid[nx][ny]) {
    				// 障碍物
    				if (dis[nx][ny] > dis[x][y] + 1) {
    					dis[nx][ny] = dis[x][y] + 1;
    					q.emplace_back(nx, ny);
    				}
    			}
    			else {
    				if (dis[nx][ny] > dis[x][y]) {
    					dis[nx][ny] = dis[x][y];
    					q.emplace_front(nx, ny);
    				}
    			}
    		}
    	}
    	return dis[n - 1][m - 1];
    }
};