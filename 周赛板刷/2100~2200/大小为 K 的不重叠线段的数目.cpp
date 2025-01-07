// https://leetcode.cn/problems/number-of-sets-of-k-non-overlapping-line-segments/



class Solution {
	static constexpr int mod = 1000000007;
	long long dp[1010][1010], f[1010][1010];
public:
    int numberOfSets(int n, int k) {
    	if (n < 2) return 0;
    	if (n == 2) return (k == 1 ? 1 : 0);
    	memset(dp, 0, sizeof(dp));
    	for (int i = 0; i < n; ++i) dp[i][0] = 1;  // 前i个数字没有线段覆盖的方法只有一个
    	for (int i = 0; i < n; ++i) f[i + 1][0] = f[i][0] + dp[i][0];
    	for (int i = 1; i < n; ++i)
    		for (int j = 1; j <= k; ++j) {
    			dp[i][j] = (dp[i - 1][j] + f[i][j - 1]) % mod;
    			f[i + 1][j] = (f[i][j] + dp[i][j]) % mod;
    		}
    	return dp[n - 1][k];
    }
};