// https://leetcode.cn/problems/count-all-possible-routes/



class Solution {
public:
	static constexpr int mod = 1e9 + 7;
    int countRoutes(vector<int>& locations, int start, int finish, int fuel) {
    	int n = locations.size();

    	vector cost(n, vector<int>(n));
    	for (int i = 0; i < n; ++i) {
    		for (int j = 0; j < n; ++j) {
    			cost[i][j] = abs(locations[i] - locations[j]);
    		}
    	}

    	vector dp(n, vector<int>(fuel + 1, 0));
    	vector vis(n, vector<bool>(fuel + 1, 0));

    	function<int(int, int)> dfs = [&](int u, int rem) -> int {
    		if (vis[u][rem]) return dp[u][rem];
            vis[u][rem] = true;
    		int res = (u == finish ? 1 : 0);
    		for (int i = 0; i < n; ++i) {
    			if (cost[u][i] <= rem)
    				res = (res + dfs(i, rem - cost[u][i])) % mod;
    		}
    		return dp[u][rem] = res;
    	};
    	return dfs(start, fuel);
    }
};