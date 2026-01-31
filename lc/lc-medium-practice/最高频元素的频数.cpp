class Solution {
public:
    int maxFrequency(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        int l = 0, ans = 0, n = nums.size();
        long long sum = 0;
        for (int i = 0; i < n; ++i) {
            if (l < i) 
                sum += 1ll * (i - l) * (nums[i] - nums[i - 1]);
            while (sum > k) {
                sum -= (nums[i] - nums[l++]);
            }
            ans = max(ans, i - l + 1);
        }
        return ans;
    }
};