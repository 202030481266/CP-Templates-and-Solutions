class Solution {
public:
    int minimizeMax(vector<int>& nums, int p) {
        sort(nums.begin(), nums.end());
        int mx = 0, n = nums.size();
        for (int i = 1; i < n; ++i) mx = max(mx, nums[i] - nums[i - 1]);
        int l = 0, r = mx, ans = -1;
        auto check = [&](int x) -> bool {
            int cnt = p;
            for (int i = 0; i < n - 1 && cnt; ++i) {
                if (nums[i + 1] - nums[i] <= x) {
                    --cnt;
                    ++i;
                }
            }
            return (cnt == 0);
        };
        while (l <= r) {
            int mid = (l + r) >> 1;
            if (check(mid)) ans = mid, r = mid - 1;
            else l = mid + 1;
        }
        return ans;
    }
};