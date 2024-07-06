#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;

// 偶数，所有的字符都是成对出现

class Solution {
public:
    int longestPalindromeSubseq(string s) {
        int n = s.size(), dp[n][n][26], ans = 0;
        memset(dp, 0, sizeof(dp));
        for (int len = 2; len <= n; len += 1) {
            for (int i = 0; i + len - 1 < n; ++i) {
                int j = i + len - 1;
                if (s[i] == s[j]) {
                    int tmp = 0;
                    if (len > 2) {
                        for (int k = 0; k < 26; ++k) {
                            if (k != s[i] - 'a') tmp = max(tmp, dp[i + 1][j - 1][k]);
                        }
                    }
                    dp[i][j][s[i] - 'a'] = tmp + 2;
                }
                for (int k = 0; k < 26; ++k) {
                    dp[i][j][k] = max(dp[i][j][k], max(dp[i+1][j][k], dp[i][j-1][k]));
                    ans = max(ans, dp[i][j][k]);
                }
            }
        }
        return ans;
    }
};