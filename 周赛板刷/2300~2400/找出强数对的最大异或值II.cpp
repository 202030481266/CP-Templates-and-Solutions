class Solution {
public:
    int maximumStrongPairXor(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int n = nums.size(), mx = nums.back();
        int high_bit = mx ? 31 - __builtin_clz(mx) : -1;

        unordered_map<int, int> h;
        int mask = 0, ans = 0, l = 0;
        for (int i = high_bit; i >= 0; --i) {
            h.clear();
            l = 0;
            mask |= (1 << i);
            int new_ans = ans | (1 << i);  // 希望能够找到 (x & mask) ^ (y & mask) == new_ans
            for (int j = 0; j < n; ++j) {
                int tmp = nums[j] & mask;
                while (nums[l] * 2 < nums[j]) h[nums[l++] & mask] -= 1;
                if (h[new_ans ^ tmp]) {
                    ans = new_ans;
                    break;
                }
                h[tmp] += 1;
            }
        }
        return ans;
    }
};