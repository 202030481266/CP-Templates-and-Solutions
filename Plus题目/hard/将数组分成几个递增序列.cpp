class Solution {
public:
    bool canDivideIntoSubsequences(vector<int>& nums, int k) {
        // 反过来思考， 为什么给出的数组是排序好的，实际上不需要排序
        // 重复的数字规定了最少的组数
        // 按照最少的组数，如果满足 group * k <= n就可以构造出来
        int mx = 0, l = 0, n = nums.size();
        for (int i = 0; i < n; ++i) {
            if (nums[i] != nums[l]) {
                // [l, i)
                mx = max(mx, i - l);
                l = i;
            }
        }
        mx = max(mx, n - l);
        return 1ll * k * mx <= 1ll * n;
    }
};