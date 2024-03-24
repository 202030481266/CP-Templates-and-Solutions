class Solution {
public:
    using ll = long long;
    long long maximumOr(vector<int>& nums, int k) {
        int n = nums.size();
        ll pre = 0;
        vector<ll> suf(n + 1);
        suf[n - 1] = nums[n - 1];
        for (int i = n - 2; i >= 0; --i)
            suf[i] = suf[i + 1] | nums[i];
        ll ans = 0;
        for (int i = 0; i < n; ++i) {
            ans = max(ans, pre | ((ll)nums[i] << k) | suf[i + 1]);
            pre |= nums[i];
        }
        return ans;
    }
};