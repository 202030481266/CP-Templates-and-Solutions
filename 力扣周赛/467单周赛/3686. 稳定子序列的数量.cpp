#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
static constexpr int mod = 1e9 + 7;
static constexpr int inf = 0x3f3f3f3f;

ll dp[2][3];

class Solution {
public:
    int countStableSubsequences(vector<int>& nums) {
        int n = nums.size();
        memset(dp, 0, sizeof(dp));
        ll a, b;
        dp[0][0] = dp[1][0] = 1;
        for (int v : nums) {
            v &= 1;
            a = dp[v ^ 1][0] + dp[v ^ 1][1] + dp[v ^ 1][2];
            b = dp[v][1];
            dp[v][1] = (dp[v][1] + a) % mod;
            dp[v][2] = (dp[v][2] + b) % mod;
        }
        int ans = 0;
        for (int i = 1; i <= 2; ++i) {
            ans = (ans + dp[0][i]) % mod;
            ans = (ans + dp[1][i]) % mod;
        }
        return ans;
    }
};