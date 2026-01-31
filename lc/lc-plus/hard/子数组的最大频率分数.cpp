int cnt[1000010];

class Solution {
public:
    static constexpr int mod = 1e9 + 7;
    using ll = long long;
    ll quick_pow(ll a, ll b) {
        if (b == 0) return 0;
        ll res = 1;
        for (; b; b >>= 1) {
            if (b & 1) res = res * a % mod;
            a = a * a % mod;
        }
        return res;
    }
    // 避免使用除法，因为这样子要求解逆元
    int maxFrequencyScore(vector<int>& nums, int k) {
        ll ans = 0, cur = 0;
        memset(cnt, 0, sizeof(cnt));
        int l = 0, n = nums.size();

        for (int i = 0; i < n; ++i) {
            ++cnt[nums[i]];
            cur = (cur + quick_pow(nums[i], cnt[nums[i]]) - quick_pow(nums[i], cnt[nums[i]] - 1) + mod) % mod;
            // [l, i]
            while (i - l + 1 > k) {
                --cnt[nums[l]];
                cur = (cur - quick_pow(nums[l], cnt[nums[l]] + 1) + quick_pow(nums[l], cnt[nums[l]]) + mod) % mod;
                ++l;
            }
            if (i >= k - 1)
                ans = max(ans, cur);
        }
        return (ans + mod) % mod;
    }
};