class Solution {
public:
    long long numberOfSubarrays(vector<int>& nums) {
        long long ans = 0;
        int n = nums.size();
        stack<pair<int, int>> s;

        for (int i = n - 1; i >= 0; --i) {
            while (!s.empty() && s.top().first < nums[i]) {
                long long c = s.top().second;
                s.pop();
                ans += c * (c + 1) / 2;
            }
            if (s.empty()) s.emplace(nums[i], 1);
            else {
                if (s.top().first == nums[i]) {
                    int c = s.top().second;
                    s.pop();
                    s.emplace(nums[i], c + 1);
                }
                else {
                    s.emplace(nums[i], 1);
                }
            }
        }
        while (!s.empty()) {
            long long c = s.top().second;
            s.pop();
            ans += c * (c + 1) / 2;
        }
        return ans;
    }
};