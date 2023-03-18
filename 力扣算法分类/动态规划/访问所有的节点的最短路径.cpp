// https://leetcode.cn/problems/shortest-path-visiting-all-nodes/
// bfs + 状态压缩


class Solution {
public:
	int shortestPathLength(vector<vector<int>>& graph) {
		int n = graph.size();
		int N = (1 << n);
		vector vis(n, vector<int>(N));  
		// 记录状态的转移情况，从所有的点出发的所有的状态最多只会经过一次，因为不存在环
		queue<tuple<int, int, int>> q;

		for (int i = 0; i < n; ++i)
			q.push({ i, (1 << i), 0 }), vis[i][(1 << i)] = true;
		while (!q.empty()) {
			auto [u, status, w] = q.front();
			q.pop();
			// dbg(u, status, w);
			if (status == (1 << n) - 1)
				return w;
			for (auto v : graph[u]) {
				int to = status | (1 << v);
				if (!vis[v][to]) {
					vis[v][to] = true;
					q.push({ v, to, w + 1 });
				}
			}
		}
		return -1;
	}
};