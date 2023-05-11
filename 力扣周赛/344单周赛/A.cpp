class Solution {
public:
    vector<int> distinctDifferenceArray(vector<int>& nums) {
        int n = nums.size();
        vector<int> s(100), p(100), cnt(100);
        for (int i = 1; i <= n; ++i) {
            s[i] = s[i - 1];
            if (!cnt[nums[i - 1]]) {
                ++s[i];
                cnt[nums[i - 1]] = 1;
            }
        }
        fill(cnt.begin(), cnt.end(), 0);
        for (int i = n; i >= 1; --i) {
            p[i] = p[i + 1];
            if (!cnt[nums[i - 1]]) {
                ++p[i];
                cnt[nums[i - 1]] = 1;
            }
        }
        vector<int> ans;
        for (int i = 1; i <= n; ++i) 
            ans.emplace_back(s[i] - p[i + 1]);
        return ans;
    }
};