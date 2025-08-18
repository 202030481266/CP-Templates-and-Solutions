#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
static constexpr int mod = 1e9 + 7;
static constexpr int inf = 0x3f3f3f3f;
static constexpr int maxn = 1e5 + 5;

ll mx[maxn], dp[maxn], sum[maxn];

class Solution {
public:
    long long minArraySum(vector<int>& nums, int k) {
        int n = nums.size();
        for (int i = 0; i < k; ++i) mx[i] = -1e15;
        for (int i = 0; i < n; ++i) {
            sum[i + 1] = sum[i] + nums[i];
            dp[i] = 0;
        }
        mx[0] = 0;
        for (int i = 1; i <= n; ++i) {
            int r = sum[i] % k;
            dp[i] = max(dp[i - 1], mx[r] + sum[i]);
            mx[r] = max(mx[r], dp[i] - sum[i]);
        }
        return sum[n] - dp[n];
    }
};