class Solution {
public:
    int maxSelectedElements(vector<int>& nums) {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        
        vector dp(n, vector<int>(2));
        unordered_map<int, int> index;
        dp[0][1] = dp[0][0] = 1;
        index[nums[0]] = 0;
        for (int i = 1; i < n; ++i) {
            dp[i][1] = dp[i][0] = 1;
            if (index.count(nums[i]))
                dp[i][1] = max(dp[i][1], dp[index[nums[i]]][0] + 1);
            if (index.count(nums[i] - 2))
                dp[i][0] = max(dp[i][0], dp[index[nums[i] - 2]][1] + 1);
            if (index.count(nums[i] - 1)) {
                dp[i][1] = max(dp[i][1], dp[index[nums[i] - 1]][1] + 1);
                dp[i][0] = max(dp[i][0], dp[index[nums[i] - 1]][0] + 1);
            }
            index[nums[i]] = i;
        }
        int ans = 0;
        for (int i = 0; i < n; ++i) 
            ans = max(ans, max(dp[i][0], dp[i][1]));
        return ans;
    }
};