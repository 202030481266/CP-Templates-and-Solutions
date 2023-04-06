// https://leetcode.cn/problems/maximum-number-of-points-with-cost/



class Solution {
public:
    long long maxPoints(vector<vector<int>>& points) {
    	int n = points.size(), m = points[0].size();

    	vector dp(2, vector<long long>(m + 2));
    	vector f(2, vector<long long>(m + 2, -0x3f3f3f3f));
    	vector g(2, vector<long long>(m + 2, -0x3f3f3f3f));

    	int cur = 0;

    	// dp[1][i] = points[0][i - 1]
		for (int i = 1; i <= m; ++i) dp[1][i] = points[0][i - 1];
    	for (int i = 1; i <= m; ++i) g[1][i] = max(g[1][i - 1], points[0][i - 1] + i * 1ll);
    	for (int i = m; i >= 1; --i) f[1][i] = max(f[1][i + 1], points[0][i - 1] - i * 1ll);

    	for (int i = 2; i <= n; ++i) {
    		for (int j = 1; j <= m; ++j) {
    			dp[cur][j] = max(g[cur ^ 1][j] - j, f[cur ^ 1][j] + j) + points[i - 1][j - 1];
    		}
    		for (int j = 1; j <= m; ++j) {
    			g[cur][j] = max(g[cur][j - 1], dp[cur][j] + j);
    		}
    		for (int j = m; j >= 1; --j) {
    			f[cur][j] = max(f[cur][j + 1], dp[cur][j] - j);
    		}
    		cur ^= 1;
    	}
    	long long ans = 0;
    	for (int i = 1; i <= m; ++i) ans = max(ans, dp[cur ^ 1][i]);
    	return ans;
    }
};