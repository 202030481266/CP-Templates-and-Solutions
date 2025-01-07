// https://leetcode.cn/problems/palindrome-partitioning-iv/



class Solution {
public:
    bool checkPartitioning(string s) {
    	int n = s.size();
    	vector dp(n + 1, vector<bool>(4, false));
    	vector f(n + 1, vector<bool>(n + 1, false));
    	for (int len = 1; len <= n; ++len) {
    		for (int i = 1; i + len - 1 <= n; ++i) {
    			int j = i + len - 1;
    			if (len == 1) f[i][j] = true;
    			else if (len == 2) f[i][j] = (s[i - 1] == s[j - 1]);
    			else {
    				f[i][j] = (f[i + 1][j - 1] && s[i - 1] == s[j - 1]);
    			}
    		}
    	}
    	dp[0][0] = true;
    	for (int i = 1; i <= n; ++i) {
    		for (int j = 1; j <= 3; ++j) {
    			for (int k = 1; k <= i; ++k) {
    				if (f[k][i]) {
    					dp[i][j] = (dp[i][j] || dp[k - 1][j - 1]);
    				}
    			}
    		}
    	}
    	return dp[n][3];
    }
};