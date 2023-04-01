// https://leetcode.cn/problems/number-of-distinct-roll-sequences/
// 经典的dp问题，只需要把影响的决策元素加到状态就好了


class Solution {
public:
	static constexpr int mod = 1000000007;
    int distinctSequences(int n) {
    	if (n == 1) return 6;

    	vector dp(n + 1, vector(7, vector<long long>(7, 0)));
    	for (int i = 1; i <= 6; ++i)
    		for (int j = 1; j <= 6; ++j) {
    			if (gcd(i, j) == 1 && i != j) {
    				dp[2][i][j] = 1;
    			}
    		}
    	for (int i = 3; i <= n; ++i) {
    		for (int j = 1; j <= 6; ++j) {
    			for (int k = 1; k <= 6; ++k) {
    				if (gcd(j, k) == 1 && j != k) {
    					for (int x = 1; x <= 6; ++x) {
    						if (x == j || x == k) continue;
    						dp[i][j][k] = (dp[i][j][k] + dp[i - 1][k][x]) % mod;
    					}
    				}
    			}
    		}
    	}
    	long long ans = 0;
    	for (int i = 1; i <= 6; ++i)
    		for (int j = 1; j <= 6; ++j)
    			ans = (ans + dp[n][i][j]) % mod;
    	return ans;
    }
};