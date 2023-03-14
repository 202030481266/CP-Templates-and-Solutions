// https://leetcode.cn/problems/find-eventual-safe-states/



class Solution {
public:
    vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
    	// DAG + 反向建图
    	int n = graph.size();
    	vector<int> g[n];
    	vector<int> du(n);
    	vector<int> ans;

    	for (int i = 0; i < n; ++i) {
    		for (int v : graph[i]) {
    			g[v].emplace_back(i);
    			++du[i];
    		}
    	}
    	for (int i = 0; i < n; ++i)
    		if (du[i] == 0) ans.emplace_back(i);
    	if (ans.size() == 0) return ans;

    	queue<int> q;
    	for (int v : ans) q.emplace(v);
    	while (!q.empty()) {
    		int u = q.front();
    		q.pop();
    		for (int v : g[u]) {
    			--du[v];
    			if (du[v] == 0) {
    				ans.emplace_back(v);
    				q.push(v);
    			}
    		}
    	}
    	sort(ans.begin(), ans.end());
    	return ans;
    }
};