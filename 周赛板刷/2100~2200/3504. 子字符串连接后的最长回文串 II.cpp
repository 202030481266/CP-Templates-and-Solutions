#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const ll llinf = 0x3f3f3f3f3f3f3f3f;



class Solution {
public:
    int ans = 0;
    vector<int> manacher(string s) {
        string ss(2 * s.size() + 1, '#');
        for (int i = 0; i < s.size(); ++i) ss[2 * i + 1] = s[i];
        int n = ss.size(), mx = 0;
        vector<int> dp(n);
        for (int i = 0, c = 0, r = 0; i < n; ++i) {
            int len = (i < r ? min(dp[2 * c - i], r - i) : 1);
            while (i - len >= 0 && i + len < n && ss[i - len] == ss[i + len]) ++len;
            if (i + len > r) {
                // 本质上在移动的时候还可以计算从某个点出发的最大回文串半径
                c = i;
                r = i + len;
            }
            dp[i] = len;
            ans = max(ans, dp[i] - 1);
        }
        vector<int> left(s.size(), 0);
        for (int i = 0; i < n; ++i) {
            int L = i - dp[i] + 1, R = i + dp[i] - 1;
            int oL = L / 2, oR = R / 2, olen = oR - oL + 1;
            if (oL < (int)s.size()) {
                left[oL] = max(left[oL], olen - 1);
            }
        }
        return left;
    }
    int longestPalindrome(string s, string t) {
        reverse(t.begin(), t.end());
        vector<int> fs = manacher(s);
        vector<int> ft = manacher(t);
        // 最长公共子串
        int n = s.size(), m = t.size();
        vector dp(n+1, vector<int>(m+1, 0));
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                if (s[i-1] == t[j-1]) {
                    dp[i][j] = dp[i-1][j-1] + 1;
                    int tmp = 0;
                    if (i + 1 <= n) tmp = max(tmp, fs[i]);
                    if (j + 1 <= m) tmp = max(tmp, ft[j]);
                    ans = max(ans, dp[i][j] * 2 + tmp);
                }
            }
        }
        return ans;
    }
};
