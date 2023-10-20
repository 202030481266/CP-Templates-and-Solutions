class Solution {
public:
    int tupleSameProduct(vector<int>& nums) {
        unordered_map<int, int> cnt;

        int n = nums.size();
        for (int i = 0; i < n; ++i)
            for (int j = i + 1; j < n; ++j)
                ++cnt[nums[i] * nums[j]];
        int ans = 0;
        for (auto [k, v] : cnt) {
            ans += v * (v - 1) * 2;
        }
        return ans;
    }
};