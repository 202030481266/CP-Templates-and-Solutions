class Solution {
public:
    int minDeletion(vector<int>& nums) {
        int ans = 0, n = nums.size();
        int last = nums[0], idx = 0;
        for (int i = 1; i < n; ++i) {
            if (nums[i] == last && idx == 0) ++ans;
            else {
                last = nums[i];
                idx ^= 1;
            }
        }
        int x = n & 1, y = ans & 1;
        if (x ^ y) ++ans;
        return ans;
    }
};