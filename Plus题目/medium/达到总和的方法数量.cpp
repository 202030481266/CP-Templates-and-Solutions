#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;

class Solution {
public:
    int numberOfWays(int n) {
        // 完全背包问题
        // 1, 2, 6
        // dp[i][j] += dp[i][j-v]
        vector<int> dp(n+1);
        vector<int> v{1,2,6};
        dp[0] = 1;
        for (int i = 0; i < 3; ++i) {
            for (int j = v[i]; j <= n; ++j) // 改变计算顺序，物品可以重复计算
                dp[j] = (dp[j] + dp[j-v[i]]) % mod;
        }
        int ans = dp[n];
        if (n >= 4) ans = (ans + dp[n-4]) % mod;
        if (n >= 8) ans = (ans + dp[n-8]) % mod;
        return ans;
    }
};