// https://leetcode.cn/problems/k-inverse-pairs-array/



class Solution {
public:
	static constexpr int mod = 1000000007;
    int kInversePairs(int n, int k) {
    	if (k == 0) return 1;

    	vector dp(2, vector<long long>(k + 1));
    	vector sum(2, vector<long long>(k + 1));
    	int cur = 0;
    	for (int i = 0; i <= k; ++i)
    		sum[cur ^ 1][i] = 1;
    	for (int i = 1; i <= n; ++i) {
    		for (int j = 0; j <= k; ++j) {
    			int l = max(0, j - i + 1);
    			if (l == 0)
    				dp[cur][j] = sum[cur ^ 1][j];
    			else 
    				dp[cur][j] = (sum[cur ^ 1][j] - sum[cur ^ 1][l - 1] + mod) % mod;
    		}
    		sum[cur][0] = dp[cur][0];
    		for (int j = 1; j <= k; ++j) {
    			sum[cur][j] = (sum[cur][j - 1] + dp[cur][j]) % mod;
    		}
    		cur ^= 1;
    	}
    	return dp[cur ^ 1][k] % mod;
    }
};