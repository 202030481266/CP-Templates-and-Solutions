// https://leetcode.cn/problems/palindromic-substrings/description/
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

class Solution {
public:
    string transform(string s) {
        string t;
        t.assign(2*s.size() + 1, '#');
        for (int i = 0; i < s.size(); ++i) 
            t[2*i + 1] = s[i];
        return t;
    } 
    int countSubstrings(string ss) {
        string s = transform(ss);
        int n = s.size(), dp[n], ans = 0;
        memset(dp, 0, sizeof(dp));
        for (int i = 0, c = 0, r = 0; i < n; ++i) {
            dp[i] = (i < r ? min(dp[2*c - i], r - i) : 1);
            while (i + dp[i] < n && i - dp[i] >= 0 && s[i + dp[i]] == s[i - dp[i]]) ++dp[i];
            if (i + dp[i] > r) c = i, r = i + dp[i];
            ans += dp[i]/2;
        }
        return ans;
    }
};