#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const ll llinf = 0x3f3f3f3f3f3f3f3f;


class Solution {
public:
    vector<long long> resultArray(vector<int>& nums, int k) {
        int n = nums.size();
        vector dp(n + 1, vector<ll>(k, 0));
        for (int i = 1; i <= n; ++i) {
            int v = nums[i-1] % k;
            dp[i][v] = 1;
            for (int pre = 0; pre < k; ++pre) {
                dp[i][(pre * v) % k] += dp[i-1][pre];
            }
        }
        vector<ll> ans(k);
        for (int i = 1; i <= n; ++i) {
            for (int j = 0; j < k; ++j) {
                ans[j] += dp[i][j];
            }
        }
        return ans;
    }
};