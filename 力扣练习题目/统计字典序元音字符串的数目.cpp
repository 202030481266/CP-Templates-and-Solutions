// https://leetcode.cn/problems/count-sorted-vowel-strings/



class Solution {
public:
	int dp[100][10];
    int countVowelStrings(int n) {
    	memset(dp, 0, sizeof(dp));

    	// a -> 0, e -> 1, i -> 2, o -> 3, u -> 4;
    	for (int i = 0; i < 5; ++i) {
    		dp[1][i] = 1;
    	}
    	for (int i = 2; i <= n; ++i) {
    		for (int j = 0; j < 5; ++j) {
    			for (int k = 0; k <= j; ++k) {
    				dp[i][j] += dp[i - 1][k];
    			}
    		}
    	}
    	int ans = 0;
    	for (int i = 0; i < 5; ++i) ans += dp[n][i];
    	return ans;
    }
};