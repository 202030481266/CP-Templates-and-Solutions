// https://leetcode.cn/problems/missing-two-lcci/
// 技巧：异或运算的性质，构造出来消失的数字的异或和，然后再分组异或


class Solution {
public:
    vector<int> missingTwo(vector<int>& nums) {
        int n = nums.size() + 2;
        vector<int> ans;

        int x = 0, pos = 0;
        for (auto c : nums) x ^= c;
        for (int i = 1; i <= n; i++) x ^= i;
        for (int i = 0; i < 32; i++) {
            if ((x >> i) & 1) {
                pos = i;
                break;
            }
        }
        int x1 = 0, x2 = 0;
        for (auto c : nums) {
            if ((c >> pos) & 1) x1 ^= c;
            else x2 ^= c;
        }
        for (int i = 1; i <= n; i++) {
            if ((i >> pos) & 1) x1 ^= i;
            else x2 ^= i;
        }
        return {x1, x2};
    }
};