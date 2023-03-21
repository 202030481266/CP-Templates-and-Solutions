class Solution {
public:
    int cnt[3000];
    int beautifulSubsets(vector<int>& nums, int k) {
        int n = nums.size();
        int ans = 0;
        sort(nums.begin(), nums.end());
        vector<int> cur;
        function<void(int)> dfs = [&](int p) {
            if (p == n) {
                ++ans;
                return;
            }
            // not take
            dfs(p + 1);
            // take
            if (nums[p] - k < 0 || (nums[p] - k >= 0 && !cnt[nums[p] - k])) {
                ++cnt[nums[p]];
                dfs(p + 1);
                --cnt[nums[p]];
            }
        };
        dfs(0);
        return ans - 1;
    }
};