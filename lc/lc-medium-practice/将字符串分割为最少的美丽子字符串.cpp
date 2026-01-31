#include <bits/stdc++.h>
using namespace std;

const string s5[8] = {
    "1",
    "101",
    "11001",
    "1111101",
    "1001110001",
    "110000110101",
    "11110100001001",
    "10011000100101101"
};
class Solution {
public:
    int minimumBeautifulSubstrings(string s) {
        int n = s.size(), dp[n+1];
        if (s[0] == '0') return -1;
        memset(dp, 0x3f, sizeof(dp));
        dp[0] = 0;
        for (int i = 1; i <= n; ++i) {
            for (int j = 0; j < 8; ++j) {
                if (s5[j].size() > i) {
                    break;
                }
                else {
                    // p
                    int len = s5[j].size(), flag = 1;
                    // [i-len+1,i]
                    for (int k = i - len + 1, x = 0; k <= i; ++k, ++x) {
                        if (s5[j][x] != s[k-1]) {
                            flag = 0;
                            break;
                        }
                    }
                    if (flag) dp[i] = min(dp[i], dp[i-len] + 1);
                }
            }
        }
        return dp[n] == 0x3f3f3f3f ? -1 : dp[n];
    }
};
