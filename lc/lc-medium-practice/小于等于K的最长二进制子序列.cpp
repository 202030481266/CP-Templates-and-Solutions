#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int longestSubsequence(string s, int k) {
        // dp + greedy  
        vector<int> a;
        vector<int> b;
        while (k) {
            b.push_back(k % 2);
            k /= 2;
        }
        for (int i = s.size() - 1; i >= 0; --i) {
            a.push_back(s[i] - '0');
        }
        if (a.size() < b.size()) return a.size(); // 不用匹配了
        // 答案至少都是m-1
        int n = a.size(), m = b.size(), cnt = 0, ans = m-1, type = 0, last0 = -1, last1 = -1;
        vector dp(n, vector<bool>(32, false));
        vector<bool> vis(m, false);
        for (int i = 0; i < n; ++i) {
            if (a[i] == 0) ++cnt;
        }
        ans = max(ans, cnt); // 全部都是零
        for (int i = 0; i < n; ++i) {
            // [0, i] 最多只能匹配到 [0, j], j <= i
            if (a[i] == 0) --cnt;
            for (int j = min(m - 1, i); j >= 0; --j) {
                if (a[i] < b[j]) {
                    dp[i][j] = (i >= j); // 无论如何都是可以匹配的, 剩下[0,i-1],[0,j-1]，数量够就行
                }
                else if (a[i] == b[j]) {
                    if (j == 0) dp[i][j] = true;
                    else {
                        if (b[j-1] == 0) {
                            if (last0 >= 0) dp[i][j] = dp[last0][j-1];
                        }
                        else {
                            if (last1 >= 0) dp[i][j] = dp[i][j] || dp[last1][j-1];
                            if (last0 >= 0) dp[i][j] = dp[i][j] || dp[last0][j-1];
                        }
                    }
                }
                if (dp[i][j] && !vis[j]) {
                    vis[j] = true;
                    ++type;
                    ans = max(ans, cnt + j + 1);
                }
            }
            if (type == m) break;
            if (a[i] == 0) last0 = i;
            else last1 = i;
        }
        return ans;
    }
};
