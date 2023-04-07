// https://leetcode.cn/problems/longest-path-with-different-adjacent-characters/



class Solution {
public:
    int longestPath(vector<int>& parent, string s) {
    	int n = parent.size();

    	// build the graph
    	vector<vector<int>> G(n);
    	for (int i = 1; i < n; ++i) {
    		G[i].emplace_back(parent[i]);
    		G[parent[i]].emplace_back(i);
    	}

    	// dfs1 预处理贡献值（包括最大值和次大值）
    	vector<int> f(n), g(n), son(n), dp(n);

    	function<int(int, int)> dfs1 = [&](int u, int fa) -> int {
    		for (int v : G[u]) {
    			if (v == fa) continue;
    			if (s[v] != s[u]) {
	    			int d = dfs1(v, u) + 1;
	    			if (d > f[u]) {
	    				g[u] = f[u];
	    				f[u] = d;
	    				son[u] = v;
	    			}
	    			else if (d > g[u]) {
	    				g[u] = d;
	    			}
	    		}
	    		else {
	    			// 搜索但是不处理
	    			dfs1(v, u);
	    		}
    		}
    		return f[u];
    	};
    	dfs1(0, -1);

    	// 换根dp
    	function<void(int,int)> dfs2 = [&](int u, int fa) {
    		for (int v : G[u]) {
    			if (v == fa) continue;
    			if (s[v] != s[u]) {
    				if (son[u] == v) dp[v] = max(dp[u], g[u]) + 1;
    				else dp[v] = max(dp[u], f[u]) + 1;
    			}
				// 搜索但是不处理 （前序遍历）
				dfs2(v, u);
    		}
    	};
    	dfs2(0, -1);

    	int ans = 0;
    	for (int i = 0; i < n; ++i) {
    		ans = max(ans, max(dp[i], f[i]));
    	}
    	return ans + 1;
    }
};