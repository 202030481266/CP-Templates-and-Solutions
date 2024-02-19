class Solution {
public:
    int twoSumLessThanK(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        int l = 0, n = nums.size(), ans = -1;
        for (int i = n - 1; i > l; --i) {
            while (l < i && nums[l] + nums[i] < k) ++l;
            if (l > 0) {
                ans = max(ans, nums[l - 1] + nums[i]);
            }
        }
        return ans;
    }
};