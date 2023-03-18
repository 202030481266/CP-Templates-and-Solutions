class Solution {
public:
    vector<int> answerQueries(vector<int>& nums, vector<int>& queries) {
        sort(nums.begin(), nums.end());

        vector<int> sum(nums.size());
        sum[0] = nums[0];
        for (int i = 1; i < nums.size(); ++i)
            sum[i] = sum[i - 1] + nums[i];

        vector<int> ans;
        for (auto c : queries) {
            auto it = lower_bound(sum.begin(), sum.end(), c);
            if (it == sum.end()) {
                ans.emplace_back(sum.size());
            }
            else if (*it == c)
                ans.emplace_back(it - sum.begin() + 1);
            else
                ans.emplace_back(it - sum.begin());
        }
        return ans;
    }
};