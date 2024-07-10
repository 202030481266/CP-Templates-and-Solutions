// https://leetcode.cn/problems/maximum-number-of-non-overlapping-palindrome-substrings/

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
    int maxPalindromes(string ss, int k) {
        // 题意就是分割出最多的回文子串
        string s = transform(ss);
        int n = s.size(), dp[n], ans = 0;
        memset(dp, 0, sizeof(dp));
        int p = -1; // 贪心
        for (int i = 0, c = 0, r = 0; i < n; ++i) {
            dp[i] = (i < r ? min(dp[2*c - i], r - i) : 1);
            while (i + dp[i] < n && i - dp[i] >= 0 && s[i + dp[i]] == s[i - dp[i]]) ++dp[i];
            if (i + dp[i] > r) c = i, r = i + dp[i];
            if (dp[i] - 1 >= k) {
                int len = dp[i] - 1, ed = (i+dp[i])/2, x = (len-k)/2;
                ed -= x;
                len -= 2*x;
                if (ed-len > p) {
                    ++ans;
                    p = ed-1;
                }
            }
        }
        return ans;
    }
};