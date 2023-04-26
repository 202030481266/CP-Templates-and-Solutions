// https://leetcode.cn/problems/count-subtrees-with-max-distance-between-cities/
// 扩展的方法来进行，思想来自于prim 生成树


class Solution {
public:
    vector<int> countSubgraphsForEachDiameter(int n, vector<vector<int>>& edges) {
    	vector<int> g[n + 1];
    	vector<int> ans(n - 1);
    	vector dis(n + 1, vector<int>(n + 1, INT_MAX));
    	for (auto c : edges) {
    		g[c[0]].emplace_back(c[1]);
    		g[c[1]].emplace_back(c[0]);
    	}
    	// caculate the distance between two nodes
    	for (int i = 1; i <= n; ++i) {
    		dis[i][i] = 0;
    		queue<int> q;
    		q.push(i);
    		while (!q.empty()) {
    			int u = q.front();
    			q.pop();
    			for (int v : g[u]) {
    				if (dis[i][v] == INT_MAX) {
    					dis[i][v] = dis[i][u] + 1;
    					q.push(v);
    				}
    			}
    		}
    	}
    	vector<int> dp(1 << (n + 1));
    	vector<int> vis(1 << (n + 1));
    	function<void(int)> dfs = [&](int S) {
    		if (vis[S]) return;
    		vis[S] = true;
    		unordered_set<int> exi;
    		vector<int> candi;
    		for (int i = 1; i <= n; ++i)
    			if ((S >> i) & 1) exi.emplace(i);
    		for (int u : exi)
    			for (int v : exi)
    				dp[S] = max(dp[S], dis[u][v]);
    		for (int u : exi) {
    			for (int v : g[u]) {
    				if (exi.count(v)) continue;
    				candi.emplace_back(v);
    			}
    		}
    		int sc = candi.size();
    		for (int i = 1; i < (1 << sc); ++i) {
    			int ns = 0;
    			for (int j = 0; j < sc; ++j)
    				if ((i >> j) & 1) ns = ns + (1 << candi[j]);
    			dfs(S | ns);
    		}
    	};
    	for (int i = 1; i <= n; ++i)
    		if (!vis[(1 << i)]) dfs(1 << i);
    	for (int i = 1; i < dp.size(); ++i)
    		if (dp[i] >= 1) ++ans[dp[i] - 1];
    	return ans;
    }
};