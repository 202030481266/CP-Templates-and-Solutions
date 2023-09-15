class Solution {
public:
    long long countInterestingSubarrays(vector<int>& nums, int modulo, int k) {
        int n = nums.size(), sum[n + 1];
        memset(sum, 0, sizeof(sum));
        for (int i = 0; i < n; ++i) {
            nums[i] %= modulo;
            if (nums[i] == k) ++sum[i + 1];
            sum[i + 1] = (sum[i + 1] + sum[i]) % modulo;
        }
        unordered_map<int, long long> h;
        h[0] = 1;
        long long ans = 0;
        for (int i = 1; i <= n; ++i) {
            ans += h[sum[i] - k];
            ans += h[sum[i] - k + modulo];
            ++h[sum[i]];
        }
        return ans;
    }
};