#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;


class Solution {
public:
    int minimumSubstringsInPartition(string s) {
        int n = s.size(), sum[26][n+1], dp[n+1];
        memset(sum, 0, sizeof(sum));
        memset(dp, 0x3f, sizeof(dp));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < 26; ++j) {
                sum[j][i+1] = sum[j][i] + (s[i] == 'a' + j);
            }
        }
        auto check = [&](int i, int j) -> bool {
            int tmp = -1;
            for (int c = 0; c < 26; ++c) {
                int s = sum[c][i] - sum[c][j-1];
                if (s > 0) {
                    if (tmp == -1) tmp = s;
                    else if (tmp != s) return false;
                }
            }
            return true;
        };
        dp[0] = 0;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= i; ++j) {
                if (check(i,j)) {
                    dp[i] = min(dp[i], dp[j-1] + 1);
                }
            }
        }
        return dp[n];
    }
};