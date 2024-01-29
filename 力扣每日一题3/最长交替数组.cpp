class Solution {
public:
    int alternatingSubarray(vector<int>& nums) {
        int n = nums.size(), ans = -1;
        int l = 0, c = 1; 
        for (int i = 1; i < n; ++i) {
            if (nums[i] - nums[i - 1] == c) {
                if (c == 1) c = -1;
                else c = 1;
            }
            else {
                // [l, i)
                if (i - l > 1) {
                    ans = max(ans, i - l);
                    l = i - 1;
                    --i;
                }
                else {
                    l = i;
                }
                c = 1;
            }
        }
        if (n - l > 1) ans = max(ans, n - l);
        return ans;
    }
};