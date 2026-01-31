class Solution {
public:
    int minOperations(vector<int>& nums, int x, int y) {
        int n = nums.size();
        int mx = *max_element(nums.begin(), nums.end());

        int r = (mx - 1) / y + 1, l = 0;

        x -= y;

        auto check = [&](int t) -> bool {
            int cnt = t;
            for (int i = 0; i < n; ++i) {
                if (nums[i] > 1ll * y * t) {
                    int sub = nums[i] - y * t;
                    cnt -= ((sub - 1) / x + 1);
                    if (cnt < 0) return false;
                }
            }
            return true;
        };

        while (l + 1 < r) {
            int mid = (l + r) >> 1;
            if (check(mid)) r = mid;
            else l = mid;
        }
        return r;
    }
};