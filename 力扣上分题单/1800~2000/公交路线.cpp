// https://leetcode.cn/problems/bus-routes/



class Solution {
public:
    int numBusesToDestination(vector<vector<int>>& routes, int source, int target) {
    	int n = routes.size();
    	unordered_map<int, vector<int>> a;
    	for (int i = 0; i < n; ++i) {
    		for (int v : routes[i]) {
    			a[v].emplace_back(i);
    		}
    	}
    	if (!a.count(source) || !a.count(target)) return -1;
    	if (source == target) return 0;
    	unordered_set<int> x;
    	queue<int> q;
    	vector<bool> vis(n, false);
    	for (auto c : a[target]) x.emplace(c);
    	for (auto c : a[source]) q.emplace(c), vis[c] = true;
    	int ans = 1;
    	while (!q.empty()) {
    		auto cur = q;
    		while (!cur.empty()) {
    			int u = cur.front();
    			cur.pop();
    			q.pop();
    			if (x.count(u)) return ans;
    			for (auto p : routes[u]) {
    				for (int v : a[p]) {
    					if (vis[v]) continue;
    					vis[v] = true;
    					q.emplace(v);
    				}
    			}
    		}
    		++ans;
    	}
    	return -1;
    }
};