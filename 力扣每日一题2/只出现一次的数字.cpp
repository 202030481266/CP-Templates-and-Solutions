class Solution {
public:
    vector<int> singleNumber(vector<int>& nums) {
        int res = 0, n = nums.size();

        // x ^ y
        for (int i = 0; i < n; ++i) res ^= nums[i];

        assert(res != 0);

        int pos = 0;
        for (int i = 0; i < 32; ++i) 
            if ((res >> i) & 1) {
                pos = i;
                break;
            }

        int x = 0, y = 0;
        for (int i = 0; i < n; ++i) {
            if ((nums[i] >> pos) & 1) x ^= nums[i];
            else y ^= nums[i];
        }
        return {x, y};
    }
};