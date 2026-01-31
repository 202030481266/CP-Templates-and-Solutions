class Solution {
public:
    int maxScore(vector<int>& nums) {
        int n = nums.size();
        sort(nums.begin(), nums.end(), greater<int>());
        vector<long long> sum(n);
        sum[0] = nums[0];
        int ans = (sum[0] > 0);
        for (int i = 1; i < n; ++i) {
            sum[i] = sum[i - 1] + nums[i];
            if (sum[i] > 0) ++ans;
        }
        return ans;
    }
};