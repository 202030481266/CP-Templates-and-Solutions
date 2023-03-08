// https://leetcode.cn/problems/count-vowels-permutation/



class Solution {
public:
	static constexpr int mod = 1000000007;
    int countVowelPermutation(int n) {
    	vector dp(n + 1, vector<long long>(5, 0));

    	// a-0, e-1, i-2, o-3, u-4

    	for (int i = 0; i < 5; ++i) dp[1][i] = 1;
    	for (int i = 2; i <= n; ++i) {
    		// five choice
    		// a, can take e, i, u
    		dp[i][0] = (dp[i - 1][1] + dp[i - 1][2] + dp[i - 1][4]) % mod;
    		// e, can take a, i 
    		dp[i][1] = (dp[i - 1][0] + dp[i - 1][2]) % mod;
    		// i, can take e, o
    		dp[i][2] = (dp[i - 1][1] + dp[i - 1][3]) % mod;
    		// o, can take i
    		dp[i][3] = dp[i - 1][2];
    		// u, can take o, i
    		dp[i][4] = (dp[i - 1][3] + dp[i - 1][2]) % mod;
    	}
    	long long ans = 0;
    	for (int i = 0; i < 5; ++i)
    		ans = (ans + dp[n][i]) % mod;
    	return ans;
    }
};