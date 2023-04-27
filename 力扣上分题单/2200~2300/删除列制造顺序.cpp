// https://leetcode.cn/problems/delete-columns-to-make-sorted-iii/
// 降维 + 动态规划


class Solution {
public:
    int minDeletionSize(vector<string>& strs) {
    	int n = strs.size(), m = strs[0].size(), f[m][m], a[m][n], dp[m];
    	memset(f, 0, sizeof(f));
    	memset(dp, 0, sizeof(dp));
    	for (int i = 0; i < m; ++i)
    		for (int j = 0; j < n; ++j) a[i][j] = strs[j][i] - 'a';
    	for (int i = 0; i < m; ++i)
    		for (int j = i + 1; j < m; ++j) {
    			bool flag = true;
    			for (int k = 0; k < n; ++k) 
    				if (a[j][k] < a[i][k]) { flag = false; break; }
    			f[i][j] = flag;
    		}
    	int ans = 0;
    	for (int i = 0; i < m; ++i) {
    		dp[i] = 1;
    		for (int j = 0; j < i; ++j)
    			if (f[j][i]) dp[i] = max(dp[i], dp[j] + 1);
    		ans = max(ans, dp[i]);
    	}
    	return m - ans;
    }
};