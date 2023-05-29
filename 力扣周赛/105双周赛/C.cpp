class Solution {
public:
    long long maxStrength(vector<int>& nums) {
        int n = nums.size();
        long long ans = -2e15;
        for (int i = 1; i < (1 << n); ++i) {
            long long tmp = 1;
            for (int j = 0; j < n; ++j) {
                if (i & (1 << j))
                    tmp *= nums[j];
            }
            ans = max(ans, tmp);
        }
        return ans;
    }
};