// https://leetcode.cn/problems/partition-array-into-two-equal-product-subsets/
using ull = unsigned long long;

class Solution {
public:
    bool checkEqualPartitions(vector<int>& nums, long long target) {
        int n = nums.size();
        double cur = 1;
        for (int i = 0; i < n; ++i) {
            if (target % nums[i]) return false;
            cur *= nums[i];
        }
        if (cur != (double)target * target) return false;
        for (int i = 0; i < (1 << n); ++i) {
            ull cur = 1;
            for (int j = 0; j < n; ++j) {
                if (i & (1 << j)) {
                    if (cur > target / nums[j]) {
                        break;
                    }
                    cur *= nums[j];
                }
            }
            if (cur == target) return true;
        }
        return false;
    }
};