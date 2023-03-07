// https://leetcode.cn/problems/chuan-di-xin-xi/



class Solution {
public:
    int numWays(int n, vector<vector<int>>& relation, int k) {
    	vector<int> g[n];

    	for (auto c : relation)
    		g[c[0]].emplace_back(c[1]);

    	vector dp(n, vector<int>(k + 1, -1));

    	function<int(int,int)> dfs = [&](int u, int s) -> int {
    		if (s == 0) {
    			return (u == n - 1) ? 1 : 0;
    		}
    		if (dp[u][s] != -1) return dp[u][s];

    		int t = 0;
    		for (auto v : g[u]) {
    			t += dfs(v, s - 1);
    		}
    		return dp[u][s] = t;
    	};
    	return dfs(0, k);
    }
};