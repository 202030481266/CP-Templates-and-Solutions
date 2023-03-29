// https://leetcode.cn/problems/most-profitable-path-in-a-tree/



class Solution {
public:
    int mostProfitablePath(vector<vector<int>>& edges, int bob, vector<int>& amount) {
    	// 确定树结构
    	int n = edges.size() + 1;

    	vector<int> fa(n); 
    	vector<vector<int>> g(n);
    	for (auto c : edges) {
    		g[c[0]].emplace_back(c[1]);
    		g[c[1]].emplace_back(c[0]);
    	}

    	function<void(int, int)> dfs1 = [&](int u, int father) {
    		fa[u] = father;
    		for (int v : g[u]) {
    			if (v == father) continue;
    			dfs1(v, u);
    		}
    	};
    	dfs1(0, -1);

    	// bob path pass
    	vector<int> f(n);
    	int father = bob, time = 1;
    	while (father != -1) {
    		f[father] = time++;
    		father = fa[father];
    	}

    	// caculate the alice path
    	int ans = INT_MIN;
    	function<void(int, int, int, int)> dfs = [&](int u, int father, int t, int sum) {
    		int gain = 0;
    		if (f[u] > 0) {
    			// bob has pass
    			if (f[u] == t) {
    				gain = amount[u] / 2;
    			}
    			else if (f[u] > t) gain = amount[u];
    		}
    		else gain = amount[u];

    		// it is a leaf
    		if (g[u].size() == 1 && u != 0) {
    			ans = max(ans, gain + sum);
    			return;
    		}
    		for (int v : g[u]) {
    			if (v != father) {
    				dfs(v, u, t + 1, sum + gain);
    			}
    		}
    	};
    	dfs(0, -1, 1, 0);
    	return ans;
    }
};:while