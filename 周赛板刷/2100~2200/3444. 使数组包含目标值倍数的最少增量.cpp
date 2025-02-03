#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const ll llinf = 0x3f3f3f3f3f3f3f3f;

class Solution {
public:
    int minimumIncrements(vector<int>& nums, vector<int>& target) {
        int n = nums.size(), m = target.size();
        vector<ll> dp(1<<m, inf);
        dp[0] = 0;
        for (int x = 0; x < n; ++x) {
            for (int i = (1<<m)-1; i > 0; --i) {
                for (int j = i; j; j = (j-1)&i) {
                    ll lcm = 1;
                    for (int k = 0; k < m; ++k) {
                        if ((j >> k) & 1) {
                            lcm = lcm * target[k] / gcd(lcm, 1ll*target[k]);
                        }
                    }
                    if (nums[x] % lcm == 0) dp[i] = min(dp[i], dp[i^j]);
                    else dp[i] = min(dp[i], dp[i^j] + lcm - (nums[x] % lcm));
                }
            }
        }
        return dp[(1<<m)-1];
    }
};