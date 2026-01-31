class Solution {
public:
    int matrixSum(vector<vector<int>>& nums) {
        for (auto& c : nums) sort(c.begin(), c.end());
        int ans = 0, m = nums[0].size(), n = nums.size();
        for (int i = 0; i < m; ++i) {
            int tmp = 0;
            for (int j = 0; j < n; ++j) tmp = max(tmp, nums[j][i]);
            ans += tmp;
        }
        return ans;
    }
};