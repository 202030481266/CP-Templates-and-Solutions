// https://leetcode.cn/problems/maximize-palindrome-length-from-subsequences/



class Solution {
public:
    int longestPalindrome(string word1, string word2) {
    	int n = word1.size(), m = word2.size(), dp[n + 1][m + 1], f[n + 1][n + 1], g[m + 1][m + 1];
    	memset(dp, 0, sizeof(dp)); 
    	memset(f, 0, sizeof(f));
    	memset(g, 0, sizeof(g));
    	reverse(word2.begin(), word2.end());
    	for (int i = 1; i <= n; ++i) f[i][i] = 1;
    	for (int i = 1; i <= m; ++i) g[i][i] = 1;
    	for (int i = n - 1; i >= 1; --i) 
    		for (int j = i + 1; j <= n; ++j)
    			f[i][j] = (word1[i - 1] == word1[j - 1] ? f[i + 1][j - 1] + 2 : max(f[i][j - 1], f[i + 1][j]));
    	for (int i = m - 1; i >= 1; --i)
    		for (int j = i + 1; j <= m; ++j)
    			g[i][j] = (word2[i - 1] == word2[j - 1] ? g[i + 1][j - 1] + 2 : max(g[i][j - 1], g[i + 1][j]));
    	for (int i = 1; i <= n; ++i)
    		for (int j = 1; j <= m; ++j) 
    			dp[i][j] = (word1[i - 1] == word2[j - 1] ? dp[i - 1][j - 1] + 1 : max(dp[i][j - 1], dp[i - 1][j]));
    	int ans = 0;
    	for (int i = 1; i <= n; ++i)
    		for (int j = 1; j <= m; ++j) {
    			if (dp[i][j] == 0) continue;
    			ans = max(ans, 2 * dp[i][j]);
    			if (i + 1 <= n) ans = max(ans, 2 * dp[i][j] + f[i + 1][n]);
    			if (j + 1 <= m) ans = max(ans, 2 * dp[i][j] + g[j + 1][m]);
    		}
    	return ans;
    }
};