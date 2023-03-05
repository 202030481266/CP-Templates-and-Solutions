// https://leetcode.cn/problems/sum-of-distances-in-tree/
// 树形dp



class Solution {
public:
    vector<int> sumOfDistancesInTree(int n, vector<vector<int>>& edges) {
    	vector<int> g[n];
    	vector<int> dis(n);
    	vector<int> siz(n);

    	for (auto c : edges) {
    		g[c[0]].emplace_back(c[1]);
    		g[c[1]].emplace_back(c[0]);
    	}

    	int res = 0;

    	function<void(int,int,int)> dfs = [&](int u, int fa, int dis) {
    		res += dis;
    		siz[u] = 1;
    		for (auto v : g[u]) {
    			if (v != fa) {
    				dfs(v, u, dis + 1);
    				siz[u] += siz[v];
    			} 
    		}
    	};
    	dfs(0, -1, 0);
    	dis[0] = res;

    	function<void(int,int)> f = [&](int u, int fa) {
    		for (auto v : g[u]) {
    			if (v != fa) {
    				dis[v] = (dis[u] + n - siz[v] * 2);
    				f(v, u);
    			}
    		}
    	};
    	f(0, -1);
    	return dis;
    }
};