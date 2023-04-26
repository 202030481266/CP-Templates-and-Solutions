// https://leetcode.cn/problems/minimum-cost-to-merge-stones/
// 区间dp模板题


class Solution {
public:
    int mergeStones(vector<int>& stones, int k) {
    	int n = stones.size();
    	// decrease every time k - 1 and last remain 1
    	if ((n - 1) % (k - 1) > 0) return -1;

    	vector<int> sum(n + 1);
    	for (int i = 1; i <= n; ++i) sum[i] = sum[i - 1] + stones[i - 1];

    	vector dp(n + 1, vector(n + 1, vector<int>(k + 1, -1)));
    	// the last step must be k stones merge as one
    	// dp[i][j][k] = Min({dp[i][x][1] + dp[x + 1][j][k - 1]});

    	/* if [i, j] can be merge as x segments
			len == x, so the cost is 0
			len > x, and we need the merge, every merge will decrease k - 1 stones
			(len - x) % (k - 1) == 0
			in conclusion, must satisfy that (len - x) % (k - 1) == 0
    	*/
    	// initialize
    	// 边界太难处理了吧，反正我觉得思路应该是有了
    	function<int(int, int, int)> dfs = [&](int i, int j, int p) -> int {
    		int &res = dp[i][j][p];
    		if (res != -1) return dp[i][j][p];
    		if (p == 1) {
    			return res = (i == j ? 0 : dfs(i, j, k) + sum[j] - sum[i - 1]);
    		}
    		res = INT_MAX;
    		for (int m = i; m < j; m += k - 1) {
    			// build the first piles
    			res = min(res, dfs(i, m, 1) + dfs(m + 1, j, p - 1));
    		}
    		return res;
    	};
    	return dfs(1, n, 1);
    }
};