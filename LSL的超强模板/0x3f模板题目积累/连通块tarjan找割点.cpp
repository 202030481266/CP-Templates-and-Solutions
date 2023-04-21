// 模板题目1，分割为两个连通分量最少操作数，最多其实就2次（边缘角落），有割点的就一次
// https://leetcode.cn/problems/minimum-number-of-days-to-disconnect-island/
class Solution {
	static constexpr int dirs[4][2] = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
public:
    int minDays(vector<vector<int>>& grid) {
    	// 1 <= m, n <= 30
    	// 突破口在于割点，如果存在割点，那么一天就够了, 如果一天不行，那么两天一定可以，因为去掉最边边的那个就可以了
    	int n = grid.size(), m = grid[0].size(), dfn[n * m], low[n * m], vis[n * m], flag[n * m], tot = 0, res = 0, cnt1 = 0;
    	memset(dfn, 0, sizeof(dfn));
    	memset(low, 0, sizeof(low));
    	memset(vis, 0, sizeof(vis));
    	memset(flag, 0, sizeof(flag));
    	vector<vector<int>> g(n * m);
    	// 建图
    	for (int i = 0; i < n; ++i)
    		for (int j = 0; j < m; ++j) 
    			if (grid[i][j]) {
    				for (int k = 0; k < 4; ++k) {
    					int nx = i + dirs[k][0], ny = j + dirs[k][1];
    					if (nx < 0 || ny < 0 || nx >= n || ny >= m || !grid[nx][ny]) continue;
    					// a -> b
    					g[i * m + j].emplace_back(nx * m + ny);
    				}
    				++cnt1;
    			}
    	if (cnt1 == 0 || cnt1 == 1) return cnt1;
    	// tarjan
    	function<void(int, int)> tarjan = [&](int u, int father) {
    		vis[u] = true;
    		low[u] = dfn[u] = ++tot;
    		int child = 0;
    		for (int v : g[u]) {
    			if (!vis[v]) {
    				++child;
    				tarjan(v, u);
    				low[u] = min(low[u], low[v]); // 通过自己的儿子到达的最小节点编号
    				if (father != u && low[v] >= dfn[u] && !flag[u]) flag[u] = true, ++res; // 存在一个满足的点
    			} else if (v != father) {
    				low[u] = min(low[u], dfn[v]); // 更新最小编号
    			}
    		}
    		if (father == u && child >= 2 && !flag[u]) flag[u] = true, ++res; // 搜索起点的判断儿子数量即可
    	};
    	int st = -1;
    	for (int i = 0; i < n; ++i) {
    		if (st != -1) break;
    		for (int j = 0; j < m; ++j) if (grid[i][j]) { st = i * m + j; break; }
    	}
    	tarjan(st, st);
    	// 一开始多个连通块，返回0
    	for (int i = 0; i < n; ++i)
    		for (int j = 0; j < m; ++j) if (grid[i][j] && !vis[i * m + j]) return 0; 
    	return (res > 0 ? 1 : 2);
    }
};