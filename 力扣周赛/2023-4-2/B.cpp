class Solution {
public:
    vector<vector<int>> findMatrix(vector<int>& nums) {
        int n = nums.size(), mx = 0;
        vector<int> cnt(n + 1);
        for (int c : nums) ++cnt[c], mx = max(mx, cnt[c]);

        vector<vector<int>> ans(mx);
        for (int i = 1; i <= n; ++i) {
            if (cnt[i]) {
                for (int j = 0; j < cnt[i]; ++j) {
                    ans[j].emplace_back(i);
                }
            }
        }
        return ans;
    }
};