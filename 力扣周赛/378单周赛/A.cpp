class Solution {
public:
    bool hasTrailingZeros(vector<int>& nums) {
        int res = 0, n = nums.size();
        for (int i = 0; i < n; ++i) {
            if (nums[i] % 2 == 0) ++res;
        }
        return res >= 2;
    }
};