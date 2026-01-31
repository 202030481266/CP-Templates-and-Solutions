#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
static constexpr int mod = 1e9 + 7;
static constexpr int inf = 0x3f3f3f3f;

static constexpr int maxn = 1000005;
int dp[maxn], mask[maxn];

// 本质上就是求解一个数字的最大的子集
class Solution {
public:
    long long maxProduct(vector<int>& nums) {
        ranges::sort(nums);
        nums.erase(unique(nums.begin(), nums.end()), nums.end());
        int n = nums.size(), mx = 0;
        for (int i = 0; i < n; ++i) {
            mask[i] = ((1 << bit_width((unsigned int)nums[i])) - 1) ^ nums[i];
            if (mask[i] > mx) mx = mask[i];
        }
        for (int i = 0; i <= mx; ++i) dp[i] = 0;
        for (int v : nums) {
            if (v <= mx) dp[v] = v;
        }
        for (int i = 1; i <= mx; ++i) { // 子集枚举到下一层即可，这样子的话，复杂度就会很高
            for (int j = 0; j < 20; ++j) {
                if ((i >> j) & 1) {
                    dp[i] = max(dp[i], dp[i ^ (1 << j)]);
                }
            }
        }
        ll ans = 0;
        for (int i = 0; i < n; ++i) {
            ans = max(ans, 1ll * dp[mask[i]] * nums[i]);
        }
        return ans;
    }
};