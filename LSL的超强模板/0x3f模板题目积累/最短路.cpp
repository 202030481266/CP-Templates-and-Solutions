// 最短路一直都是图论最热门和最重要的一类问题
// 大部分最短路问题都可以使用最短路算法解决，但是最难的地方在于正确的图建模


// 难题模板1：https://leetcode.cn/problems/minimum-time-to-visit-a-cell-in-a-grid/description/
// 具有时间性质的最短路问题
/*
	1、不能在格子上停留，表明每一个时间都要移动（暗示可以反复横跳）
	2、格子具有时间性质，只有超过固定的时间才能移动到这个格子上。
	3、一种通用的做法就是二分答案+bfs就可以得到答案（具体可以看bfs技巧）
	4、另外一种方法是单独分析问题的性质，由于反复横跳的原因，那么可以得到到达[i, j]的最早时间dis[i][j]一定与i+j的奇偶性相同
*/
class Solution {
public:
    int minimumTime(vector<vector<int>>& grid) {
    	if (grid[0][1] > 1 && grid[1][0] > 1) return -1; // 特殊情况判断

    	int n = grid.size(), m = grid[0].size(), dis[n][m];
    	int dx[] = {-1, 1, 0, 0};
    	int dy[] = {0, 0, -1, 1};
    	memset(dis, 0x3f, sizeof(dis));

    	// dijkstra
    	priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> q;
    	q.emplace(0, 0, 0);
    	dis[0][0] = 0;
    	while (!q.empty()) {
    		auto [d, x, y] = q.top();
    		q.pop();
    		if (x == n - 1 && y == m - 1) return d;
    		for (int i = 0; i < 4; ++i) {
    			int nx = x + dx[i], ny = y + dy[i];
    			if (nx < 0 || ny < 0 || nx >= n || ny >= m) continue;
    			int tmp = max(d + 1, grid[nx][ny]);
    			tmp += (tmp - nx - ny) % 2;
    			if (tmp < dis[nx][ny]) {
    				dis[nx][ny] = tmp;
    				q.emplace(tmp, nx, ny);
    			}
    		}
    	}
    	for (int i = 0; i < n; ++i) {
    		for (int j = 0 ;j < m;++j) printf("%d ", dis[i][j]);
    		cout << '\n';
    	}
    	return -1;
    }
};

