// https://leetcode.cn/problems/maximum-product-of-first-and-last-elements-of-a-subsequence/description/
using ll = long long;

static constexpr int inf = 0x3f3f3f3f;

class Solution {
public:
    long long maximumProduct(vector<int>& nums, int m) {
        int n = nums.size();
        vector<ll> mn(n + 1), mx(n + 1);
        mn[0] = inf;
        mx[0] = -inf;
        for (int i = 1; i <= nums.size(); ++i) {
            mn[i] = min((ll)nums[i - 1], mn[i - 1]);
            mx[i] = max((ll)nums[i - 1], mx[i - 1]);
        }
        ll res = -1e10;
        ll a = -inf, b = inf;
        for (int i = n; i > m - 1; --i) { // [1, m-1]
            // [i - m + 1 , i]
            a = max(a, (ll)nums[i - 1]);
            b = min(b, (ll)nums[i - 1]);
            res = max(res, a * mx[i - m + 1]);
            res = max(res, b * mn[i - m + 1]);
        }
        return res;
    }
};