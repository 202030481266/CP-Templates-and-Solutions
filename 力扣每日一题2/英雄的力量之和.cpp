class Solution {
    static constexpr int mod = 1e9 + 7;
public:
    int sumOfPower(vector<int>& nums) {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        long long ans = 0, res = 0;
        for (int i = 1; i < n; ++i) {
            res = (res * 2 % mod + nums[i - 1]) % mod;
            ans = (ans + res * nums[i] % mod * nums[i] % mod) % mod;
        }
        for (int i = 0; i < n; ++i) ans = (1ll * nums[i] * nums[i] % mod * nums[i] % mod + ans) % mod;
        return ans;
    }
};