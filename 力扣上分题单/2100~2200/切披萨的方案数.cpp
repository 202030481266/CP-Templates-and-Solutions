// https://leetcode.cn/problems/number-of-ways-of-cutting-a-pizza/
// 这道题目的关键在于每一次切都只会缩小，并且保留的区域是右下方的子矩阵，所以很明显是dp


class Solution {
public:
	static constexpr int mod = 1000000007;
    int ways(vector<string>& pizza, int k) {
    	int n = pizza.size(), m = pizza[0].size();

    	vector dp(n + 1, vector(m + 1, vector<int>(k + 1, -1)));
    	vector a(n + 1, vector<int>(m + 1, 0));

    	for (int i = 1; i <= n; ++i) 
    		for (int j = 1; j <= m; ++j) 
    			a[i][j] = a[i][j - 1] + a[i - 1][j] - a[i - 1][j - 1] + (pizza[i - 1][j - 1] == 'A');

    	auto f = [&](int x2, int y2, int x1, int y1) -> int {
    		return a[x2][y2] - a[x2][y1 - 1] - a[x1 - 1][y2] + a[x1 - 1][y1 - 1];
    	};

    	function<int(int, int, int)> dfs = [&](int i, int j, int p) -> int {
    		if (p == 1) 
    			return f(n, m, i, j) > 0;
    		int &res = dp[i][j][p];
    		if (res != -1) return res;
    		res = 0;
    		// 横着切
    		for (int x = i; x < n; ++x) {
    			// [i...x] rows is assigned
    			// [i, j] ~ [x, m]
    			if (f(x, m, i, j) > 0) {
    				res = (res + dfs(x + 1, j, p - 1)) % mod;
    			}
    		}
    		// 竖着切
    		for (int x = j; x < m; ++x) {
    			// [j..x] cols is assigned
    			// [i, j] ~ [n, x]
    			if (f(n, x, i, j) > 0) {
    				res = (res + dfs(i, x + 1, p - 1)) % mod;
    			}
    		}
    		return res;
    	};
    	return dfs(1, 1, k);
    }
};