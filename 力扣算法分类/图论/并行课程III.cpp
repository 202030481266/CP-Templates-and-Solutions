// https://leetcode.cn/problems/parallel-courses-iii/



class Solution {
public:
    int minimumTime(int n, vector<vector<int>>& relations, vector<int>& t) {
    	vector<int> deg(n + 1);
    	vector<int> time(n + 1);
    	vector<vector<int>> g(n + 1);

    	for (auto e : relations) {
    		g[e[0]].emplace_back(e[1]);
    		++deg[e[1]];
    	}
    	queue<int> q;
    	for (int i = 1; i <= n; ++i) {
    		if (deg[i] == 0) {
    			q.push(i);
    			time[i] = t[i - 1];
    		}
    	}
    	while (!q.empty()) {
    		int u = q.front();
    		q.pop();
    		for (int v : g[u]) {
    			--deg[v];
    			time[v] = max(time[v], time[u]);
    			if (deg[v] == 0) {
    				time[v] += t[v - 1];
    				q.push(v);
    			}
    		}
    	}
    	int ans = 0;
    	for (int i = 1; i <= n; ++i) {
    		ans = max(ans, time[i]);
    	}
    	return ans;
    }
};