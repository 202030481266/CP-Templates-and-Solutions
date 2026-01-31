class Solution {
public:
    int dp(vector<int>& a, int l, int r) {
        // [l, r)
        int f0 = 0, f1 = 0;
        for (int i = l; i < r; ++i) {
            int x = max(f1, f0 + a[i]);
            f0 = f1;
            f1 = x;
        }
        return f1;
    }
    int rob(vector<int>& nums) {
        int n = nums.size();
        // 根据0是否取分类
        return max(nums[0] + dp(nums, 2, n - 1), dp(nums, 1, n));
    }
};