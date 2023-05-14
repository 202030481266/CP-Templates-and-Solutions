// https://leetcode.cn/problems/reachable-nodes-in-subdivided-graph/



class Solution {
	typedef long long ll;
	typedef pair<int, int> pii;
	typedef pair<ll, ll> pll;
public:
    int reachableNodes(vector<vector<int>>& edges, int maxMoves, int n) {
    	vector<pll> g[n];
    	for (auto &e : edges) {
    		g[e[0]].emplace_back(e[1], e[2] + 1);
    		g[e[1]].emplace_back(e[0], e[2] + 1);
    	}
    	// 最短路
    	vector<ll> dis(n, 2e10);
    	priority_queue<pll, vector<pll>, greater<pll>> q;
    	dis[0] = 0;
    	q.emplace(0, 0);
    	while (!q.empty()) {
    		auto [d, u] = q.top();
    		q.pop();
    		if (d != dis[u]) continue;
    		for (auto [v, w] : g[u]) {
    			if (dis[v] > d + w) {
    				dis[v] = d + w;
    				q.emplace(dis[v], v);
    			}
    		}
    	}
    	// 统计边节点贡献
    	int ans = 0;
    	for (auto &e : edges) {
    		ll du = dis[e[0]], dv = dis[e[1]], cu = 0, cv = 0;
    		if (du < 1ll * maxMoves) cu = maxMoves - du;
    		if (dv < 1ll * maxMoves) cv = maxMoves - dv;
    		ans += min(cu + cv, 1ll * e[2]);
    	}
    	for (int i = 0; i < n; ++i) 
    		if (dis[i] <= maxMoves * 1ll) ++ans;
    	return ans;
    }
};