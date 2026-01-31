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


// dijkstra次短路问题模板
// https://leetcode.cn/problems/second-minimum-time-to-reach-destination/
// 可变的次短路问题（本质就是动态规划）
class Solution {
public:
	typedef pair<int, int> pii;
    int secondMinimum(int n, vector<vector<int>>& edges, int time, int change) {
    	// 所有的节点都是绿色开始，并且只有绿色的时候才能离开节点
    	// 求解的是严格第二小值， 节点 1 到节点 n 需要的 第二短时间，感觉就是次短路问题
    	// color[i] = ((cur / change) & 1 ? red : green)
    	vector<vector<int>> g(n);
    	vector<int> dis1(n, 0x3f3f3f3f), dis2(n, 0x3f3f3f3f);
    	dis1[0] = 0;
    	for (auto &e : edges) {
    		--e[0], --e[1];
    		g[e[0]].emplace_back(e[1]);
    		g[e[1]].emplace_back(e[0]);
    	}
    	priority_queue<pii, vector<pii>, greater<pii>> q; 
    	q.emplace(0, 0);
    	while (!q.empty()) {
    		auto [d, u] = q.top();
    		q.pop();
    		if (dis2[u] < d) continue;
    		// d是到达u的时间
    		for (int v : g[u]) {
    			int dis;
				// 到达u的时候是绿灯
				if ((d / change) % 2 == 0) dis = d + time;
				// 到达u的时候是红灯
				else dis = d + time + change - (d % change);
				if (dis1[v] > dis) {
					swap(dis1[v], dis);
					q.emplace(dis1[v], v);
				}
				if (dis2[v] > dis && dis1[v] < dis) {
					dis2[v] = dis;
					q.emplace(dis2[v], v);
				}
    		}
    	}
    	return dis2[n - 1];
    }
};