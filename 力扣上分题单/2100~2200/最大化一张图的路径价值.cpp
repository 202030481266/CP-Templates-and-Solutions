// https://leetcode.cn/problems/maximum-path-quality-of-a-graph/



class Solution {
public:
    int maximalPathQuality(vector<int>& values, vector<vector<int>>& edges, int maxTime) {
    	// 每个节点的价值 至多 算入价值总和中一次
    	// 每个节点 至多 有 四条 边与之相连
    	int n = values.size(), dis[n];
    	memset(dis, 0x3f, sizeof(dis));

    	vector<vector<pair<int, int>>> g(n);
    	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
    	for (auto &c : edges) 
    		g[c[0]].emplace_back(c[1], c[2]), g[c[1]].emplace_back(c[0], c[2]);
    	dis[0] = 0;
    	q.emplace(0, 0);
    	while (!q.empty()) {
    		auto [d, u] = q.top();
    		q.pop();
    		if (dis[u] != d) continue;
    		for (auto [v, w] : g[u]) {
    			if (dis[v] > w + d) {
    				dis[v] = w + d;
    				q.emplace(dis[v], v);
    			}
    		}
    	}
    	// 感觉除了爆搜没啥方法，因为路径可以非常复杂和变化多端
    	int ans = 0;
    	function<void(int, int, int)> dfs = [&](int u, int sum, int time) {
    		if (u == 0) ans = max(ans, sum);
    		for (auto [v, w] : g[u]) {
    			// 必须还要有足够的时间回去（这个非常重要，相当于A*搜索，效率很高）
    			if (time - w >= dis[v]) {
    				int k = values[v];
    				values[v] = 0;  // 已经加过了只能加一次
    				dfs(v, sum + k, time - w);
    				values[v] = k;// 回溯
    			}
    		}
    	};
		int tmp = values[0];
    	values[0] = 0;
    	dfs(0, tmp, maxTime);
    	return ans;
    }
};