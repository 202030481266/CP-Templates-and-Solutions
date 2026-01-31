// https://leetcode.cn/problems/longest-palindromic-substring/

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

// 扩展回文串结束位置 / 2 = 真实回文串结束位置
class Solution {
public:
    string transform(string s) {
        string t;
        t.assign(2*s.size() + 1, '#');
        for (int i = 0; i < s.size(); ++i) 
            t[2*i + 1] = s[i];
        return t;
    } 
    string longestPalindrome(string ss) {
        string s = transform(ss);
        int n = s.size(), dp[n], mx = 0;
        memset(dp, 0, sizeof(dp));
        for (int i = 0, c = 0, r = 0; i < n; ++i) {
            dp[i] = (i < r ? min(dp[2*c - i], r - i) : 1);
            while (i + dp[i] < n && i - dp[i] >= 0 && s[i + dp[i]] == s[i - dp[i]]) ++dp[i];
            if (i + dp[i] > r) c = i, r = i + dp[i];
            if (dp[i] > dp[mx]) mx = i;
        }
        int len = dp[mx]-1, ed = (mx+dp[mx])/2;
        return ss.substr(ed-len, len);
    }
};