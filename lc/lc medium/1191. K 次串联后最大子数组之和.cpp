#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const ll llinf = 0x3f3f3f3f3f3f3f3f;

class Solution {
public:
    int kConcatenationMaxSum(vector<int>& arr, int k) {
        int n = arr.size();
        vector<ll> dp(n), pre(n), suf(n);
        for (int i = 0; i < n; ++i) {
            dp[i] = arr[i];
            if (i > 0 && dp[i - 1] > 0) dp[i] += dp[i - 1];
        }
        pre[0] = arr[0];
        for (int i = 1; i < n; ++i) pre[i] = pre[i - 1] + arr[i];
        suf[n - 1] = arr[n - 1];
        for (int i = n - 2; i >= 0; --i) suf[i] = suf[i + 1] + arr[i];
        ll mx_suf = *max_element(suf.begin(), suf.end());
        ll mx_pre = *max_element(pre.begin(), pre.end());
        ll mx_dp = *max_element(dp.begin(), dp.end());
        if (k == 1) return max(0ll, mx_dp);
        ll sum = accumulate(arr.begin(), arr.end(), 0ll);
        if (sum <= 0 || k == 2) return max(mx_dp, max(0ll, mx_suf + mx_pre)) % mod;
        ll res = max(mx_dp*1ll, max(0ll, mx_suf + mx_pre + (ll)sum * (k - 2)));
        if (res >= 1ll*mx_dp) return res % mod;
        return mx_dp;
    }
};