// https://leetcode.cn/problems/stone-game-v/



class Solution {
public:
    int stoneGameV(vector<int>& stoneValue) {
    	int n = stoneValue.size();

    	vector dp(n + 1, vector<int>(n + 1, -1));
    	vector<int> sum(n + 1);
    	for (int i = 1; i <= n; ++i)
    		sum[i] = sum[i - 1] + stoneValue[i - 1];

    	function<int(int, int)> dfs = [&](int l, int r) -> int {
    		if (dp[l][r] != -1) return dp[l][r];
    		if (l >= r) return 0;
    		// left part is l..i and the right part is i + 1..r
    		int res = 0;
    		for (int i = l; i < r; ++i) {
    			int left = sum[i] - sum[l - 1];
    			int right = sum[r] - sum[i];
    			if (left > right) {
    				res = max(res, right + dfs(i + 1, r));
    			}
    			else if (left < right) {
    				res = max(res, left + dfs(l, i));
    			}
    			else {
    				int tmp = max(right + dfs(i + 1, r), left + dfs(l, i));
    				res = max(res, tmp);
    			}
    		}
    		return dp[l][r] = res;
    	};
    	return dfs(1, n);
    }
};