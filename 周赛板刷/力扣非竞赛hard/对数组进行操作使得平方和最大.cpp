class Solution {
    static constexpr int mod = 1e9 + 7;
public:
    int maxSum(vector<int>& nums, int k) {
        vector<long long> cnt(32, 0); 
        for (int i = 0; i < 32; ++i) 
            for (int& v : nums) 
                if ((v >> i) & 1) ++cnt[i];
        long long ans = 0;
        while (k > 0) {
            int mn = INT_MAX;
            for (int i = 0; i < 32; ++i)
                if (cnt[i] > 0 && cnt[i] < mn) mn = cnt[i];
            if (mn == INT_MAX) break;
            int num = min(k, mn);
            k -= num;
            long long tmp = 0;
            for (int i = 0; i < 32; ++i)
                if (cnt[i] >= mn) tmp += (1 << i), cnt[i] -= mn;
            ans = (ans + num * (tmp * tmp % mod) % mod) % mod;
        }
        return ans;
    }
};