class Solution {
public:
    long long beautifulSubarrays(vector<int>& nums) {
        long long ans = 0;
        unordered_map<int, int> h;

        int cur = 0;
        ++h[0];
        for (int i = 1; i <= nums.size(); ++i) {
            cur ^= nums[i - 1];
            ans += h[cur];
            ++h[cur];
        }
        return ans;
    }
};