#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vii = vector<vector<int>>;
using vl = vector<ll>;
using vll = vector<vector<ll>>;
static constexpr int MAXN = 200005;
static constexpr int MOD = 1e9 + 7;
static constexpr int INF = 0x3f3f3f3f;


class Solution {
public:
    int alternatingXOR(vector<int>& nums, int target1, int target2) {
        // dp[i][0] = sum of dp[j][1] if si ^ sj = target1 -> sj = si ^ target1
        // dp[i][1] = sum of dp[j][0] if si ^ sj = target2 -> sj = si ^ target2
        int n = nums.size();
        vi rk(n + 1);
        vi sum(n + 1);
        vi b{0};
        for (int i = 1; i <= n; ++i) {
            sum[i] = sum[i - 1] ^ nums[i - 1];
            b.push_back(sum[i]);
            b.push_back(sum[i] ^ target1);
            b.push_back(sum[i] ^ target2);
        }
        ranges::sort(b);
        b.erase(unique(b.begin(), b.end()), b.end());
        vl cnt0(b.size()), cnt1(b.size());
        cnt1[0] = 1;
        ll ans = 0;
        for (int i = 1; i <= n; ++i) {
            int s1 = lower_bound(b.begin(), b.end(), sum[i]) - b.begin();
            int s2 = lower_bound(b.begin(), b.end(), sum[i] ^ target1) - b.begin();
            int s3 = lower_bound(b.begin(), b.end(), sum[i] ^ target2) - b.begin();
            ll x = cnt1[s2], y = cnt0[s3];
            if (i < n) {
                cnt0[s1] = (cnt0[s1] + x) % MOD;
                cnt1[s1] = (cnt1[s1] + y) % MOD;
            }
            else ans = (ans + x + y) % MOD;
        }
        return ans;
    }
};
