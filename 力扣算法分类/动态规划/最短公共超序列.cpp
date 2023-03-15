// https://leetcode.cn/problems/shortest-common-supersequence/



class Solution {
public:
	string shortestCommonSupersequence(string str1, string str2) {
        int n = str1.length(), m = str2.length();
        vector dp(n + 1, vector<int>(m + 1));

        // LCS
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                if (str1[i - 1] == str2[j - 1])
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                else dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
        int x = n, y = m;
        string ans;
        // the LCS string
        while (x > 0 && y > 0) {
            // dbg(x, y);
            if (str1[x - 1] == str2[y - 1]) {
                ans.push_back(str1[--x]);
                --y;
            }
            else if (dp[x - 1][y] < dp[x][y - 1]) --y;
            else if (dp[x][y - 1] <= dp[x - 1][y]) --x;
        }
        if (ans.size() == 0) return str1 + str2;
        reverse(ans.begin(), ans.end());
        // dbg(ans);
        // construct the ans string
        int i = 0, j = 0, p = 0;
        vector<char> res;
        while (i < n || j < m) {
            if (i == n) res.push_back(str2[j++]);
            else if (j == m) res.push_back(str1[i++]);
            else if (str1[i] == ans[p] && str2[j] != ans[p]) {
                res.push_back(str2[j++]);
            }
            else if (str1[i] != ans[p] && str2[j] == ans[p]) {
                res.push_back(str1[i++]);
            }
            else if (str1[i] == ans[p] && str2[j] == ans[p]) {
                res.push_back(ans[p++]);
                ++i, ++j;
            }
            else {
                res.push_back(str1[i++]);
            }
        }
        string ss;
        for (char ch : res) ss += ch;
        // dbg(ss);
        return ss;
    }
};