// https://leetcode.cn/problems/soup-servings/
// 数学+动态规划(最离谱的是利用了数字的范围)
// 很傻逼的题目


class Solution {
public:
    double soupServings(int n) {

    	vector dp(201 * 25, vector<double>(201 * 25, -1));

    	function<double(int,int)> dfs = [&](int x, int y) -> double {
    		if (x <= 0 && y > 0) return 1;
    		if (x <= 0 && y <= 0) return 0.5;
    		if (y <= 0 && x > 0) return 0;
    		if (dp[x][y] != -1) return dp[x][y];
    		double temp = 0;
    		temp += dfs(x - 100, y) * 0.25;
    		temp += dfs(x - 75, y - 25) * 0.25;
    		temp += dfs(x - 50, y - 50) * 0.25;
    		temp += dfs(x - 25, y - 75) * 0.25;
    		return dp[x][y] = temp;
    	};
        n = min(200 * 25, n);
    	return dfs(n, n);
    }
};