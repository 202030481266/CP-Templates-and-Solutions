// https://leetcode.cn/problems/minimum-score-triangulation-of-polygon/
// 区间动态规划问题


class Solution {
public:
    int minScoreTriangulation(vector<int>& values) {
    	int n = values.size();

    	vector dp(n, vector<int>(n, -1));

    	function<int(int,int)> dfs = [&](int x, int y) -> int {
    		if (y - x <= 1) return 0;
    		int &res = dp[x][y];
    		if (res != -1) return dp[x][y];
    		res = 0x3f3f3f3f;
    		for (int i = x + 1; i < y; ++i) {
    			res = min(res, values[x] * values[i] * values[y] + dfs(x, i) + dfs(i, y));
    		}
    		return res;
    	};
    	return dfs(0, n - 1);
    }
};