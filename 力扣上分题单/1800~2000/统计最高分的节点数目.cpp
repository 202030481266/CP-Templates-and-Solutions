// https://leetcode.cn/problems/count-nodes-with-the-highest-score/



class Solution {
public:
    int countHighestScoreNodes(vector<int>& parents) {
    	int n = parents.size();

    	vector<int> siz(n);
    	vector<int> g[n];

    	for (int i = 1; i < n; ++i) {
    		g[i].emplace_back(parents[i]);
    		g[parents[i]].emplace_back(i);
    	}

    	function<void(int)> dfs = [&](int u) {
    		siz[u] = 1;
    		for (auto v : g[u]) {
    			if (v == parents[u]) continue;
    			dfs(v);
    			siz[u] += siz[v];
    		}
    	};
    	dfs(0);
    	long long ans = 0, res = 0;
    	for (int i = 0; i < n; ++i) {
    		long long t = max(1, siz[0] - siz[i]);
            for (auto v : g[i]) {
                if (v == parents[i]) continue;
                else t = t * siz[v];
            }
    		if (ans < t) {
    			res = 1;
    			ans = t;
    		} 
    		else if (ans == t) ++res;
    	}
    	return res;
    }
};