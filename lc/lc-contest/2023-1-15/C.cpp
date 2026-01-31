class Solution {
public:
    long long countGood(vector<int>& nums, int k) {
        long long n = nums.size();
        unordered_map<int, long long> hash;
        // slide window
        long long l = 0, r = 0, cur = 0;
        long long ans = 0;
        while (r < n) {
            while (r < n && cur < k) {
                if (hash[nums[r]]) cur += hash[nums[r]];
                ++hash[nums[r++]];
            }
            if (cur >= k) ans += (n - r + 1);
            while (l < r && cur >= k) {
                int cnt = hash[nums[l]];
                if (cnt >= 2) cur -= (cnt - 1);
                --hash[nums[l]];
                ++l;
                if (cur >= k) ans += (n - r + 1);
            }
        }
        return ans;
    }
};