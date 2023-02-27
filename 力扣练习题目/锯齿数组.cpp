class Solution {
public:
    int movesToMakeZigzag(vector<int>& nums) {
        int n = nums.size();

        // only two types
        int a = 0;
        int ans = INT_MAX;

        // even index
        for (int i = 1; i < n; i += 2) {
            int t = INT_MAX;
            if (i - 1 >= 0) {
                t = min(t, nums[i - 1]);
            }
            if (i + 1 < n) {
                t = min(t, nums[i + 1]);
            }
            if (t <= nums[i]) {
                a += (nums[i] - t + 1);
            }
        }
        ans = min(ans, a);
        a = 0;
        // odd index
        for (int i = 0; i < n; i += 2) {
            int t = INT_MAX;
            if (i - 1 >= 0) {
                t = min(t, nums[i - 1]);
            }
            if (i + 1 < n) {
                t = min(t, nums[i + 1]);
            }
            if (t <= nums[i]) {
                a += (nums[i] - t + 1);
            }
        }
        return min(ans, a);
    }
};