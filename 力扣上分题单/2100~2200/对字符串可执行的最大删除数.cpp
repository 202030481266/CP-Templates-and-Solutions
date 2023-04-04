// https://leetcode.cn/problems/maximum-deletions-on-a-string/



class Solution {
public:
    int deleteString(string s) {
        int n = s.size();

        vector<int> dp(n, -1);
        vector f(n + 1, vector<int>(n + 1, 0));

        // LCP
        // 前缀公共长度，不能暴力，否则超时
        for (int i = n - 1; i >= 0; --i) 
        	for (int j = n - 1; j >= 0; --j)
				if (s[i] == s[j])
        			f[i][j] = f[i + 1][j + 1] + 1;

        function<int(int)> dfs = [&](int i) -> int {
        	// [i, n - 1] max operations
        	if (dp[i] != -1) return dp[i];
        	int &res = dp[i];
        	res = 0;
        	for (int len = 1; len <= (n - i) / 2; ++len) {
        		if (f[i][i + len] >= len) {
        			res = max(res, 1 + dfs(i + len));
        		}
        	}
        	if (res == 0) res = 1;
        	return res;
        };
        return dfs(0);
    }
};