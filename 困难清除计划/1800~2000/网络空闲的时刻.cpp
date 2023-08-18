// https://leetcode.cn/problems/the-time-when-the-network-becomes-idle/



class Solution {
public:
    int networkBecomesIdle(vector<vector<int>>& edges, vector<int>& patience) {
    	int n = patience.size();
    	vector<int> dis(n, 0);
    	vector<int> g[n];

    	for (auto e : edges)
    		g[e[0]].emplace_back(e[1]), g[e[1]].emplace_back(e[0]);

    	// bfs
    	queue<int> q;
    	q.emplace(0);
    	while (!q.empty()) {
    		int u = q.front();
    		q.pop();
    		for (auto v : g[u])
    			if (!dis[v]) {
    				dis[v] = dis[u] + 1;
    				q.emplace(v);
    			}
    	}

    	int ans = INT_MIN;
    	for (int i = 1; i < n; ++i) {
    		int t = (2 * dis[i] - 1) / patience[i];
    		ans = max(ans, t * patience[i] + 2 * dis[i]);
    	}
    	return ans + 1;
    }
};