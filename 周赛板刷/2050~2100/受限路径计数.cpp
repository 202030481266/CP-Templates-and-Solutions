// https://leetcode.cn/problems/number-of-restricted-paths-from-first-to-last-node/



class Solution {
public:
	static constexpr int mod = 1000000007;
    int countRestrictedPaths(int n, vector<vector<int>>& edges) {
    	vector<vector<pair<int, long long>>> g(n + 1);

    	for (auto c : edges) {
    		g[c[0]].emplace_back(make_pair(c[1], 1ll * c[2]));
    		g[c[1]].emplace_back(make_pair(c[0], 1ll * c[2]));
    	}

    	// shortest path
    	priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> q;
    	vector<long long> dis(n + 1, 0x3f3f3f3f3f3f3f3f);
    	dis[n] = 0;
    	q.emplace(0, n);
    	while (!q.empty()) {
    		auto [d, u] = q.top();
    		q.pop();
    		if (dis[u] != d) continue;
    		for (auto [v, w] : g[u]) {
    			if (dis[v] > d + w) {
    				dis[v] = d + w;
    				q.emplace(dis[v], v);
    			}
    		}
    	}

    	// rebuild the graph to directed
    	vector<vector<int>> G(n + 1);
    	for (auto c : edges) {
    		if (dis[c[0]] > dis[c[1]]) G[c[0]].emplace_back(c[1]);
    		if (dis[c[0]] < dis[c[1]]) G[c[1]].emplace_back(c[0]);
    	}
    	// dfs and dp
    	vector<long long> dp(n + 1, -1);
        dp[n] = 1;
    	function<int(int)> dfs = [&](int u) -> int {
    		if (dp[u] != -1) return dp[u];
    		long long res = 0;
    		for (auto v : G[u]) {
    			res = (res + dfs(v)) % mod;
    		}
    		return dp[u] = res;
    	};
    	dfs(1);
    	return dp[1] == -1 ? 0 : dp[1];
    }
};