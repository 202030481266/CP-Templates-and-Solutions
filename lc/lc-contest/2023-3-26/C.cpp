class Solution {
public:
    vector<long long> minOperations(vector<int>& nums, vector<int>& queries) {
        int n = nums.size(), m = queries.size();
        sort(nums.begin(), nums.end());

        vector<long long> sum(n + 1);
        for (int i = 1; i <= n; ++i)
            sum[i] = sum[i - 1] + nums[i - 1];

        vector<long long> ans;
        for (int k : queries) {
            auto it = upper_bound(nums.begin(), nums.end(), k);
            long long res = 0;
            if (it == nums.begin()) {
                // means all the numbers  > k
                res = sum[n] - 1ll * k * n;
            }
            else if (it == nums.end()) {
                // means all the numbers is <= k
                res = 1ll * k * n - sum[n];
            }
            else {
                int x = it - nums.begin();
                res = 1ll * k * x - 1ll * k * (n - x) + sum[n] - 2ll * sum[x];
            }
            ans.emplace_back(res);
        }
        return ans;
    }
};