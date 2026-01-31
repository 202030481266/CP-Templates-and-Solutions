#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int longestIdealString(string s, int k) {
        int n = s.size(), dp[n], mx[26];
        memset(dp, 0, sizeof(dp));
        memset(mx, 0, sizeof(mx));
        for (int i = 0; i < n; ++i) {
            // dp[i] = max(dp[j]) + 1, abs(s[i] - s[j]) <= k
            for (int j = max(0, s[i]-'a'-k); j <= min(25, s[i]-'a'+k); ++j) {
                dp[i] = max(dp[i], mx[j] + 1);
            }
            mx[s[i]-'a'] = max(mx[s[i]-'a'], dp[i]); 
        }
        return *max_element(dp, dp+n);
    }
};
