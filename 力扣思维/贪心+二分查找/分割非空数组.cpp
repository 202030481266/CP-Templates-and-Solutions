// https://leetcode.cn/problems/split-array-largest-sum/description/
// 此题判断难度很小，贪心是最有效的算法

class Solution {
public:
    int splitArray(vector<int>& nums, int k) {
        int n = nums.size();
        int l = *max_element(nums.begin(), nums.end());
        int r = accumulate(nums.begin(), nums.end(), 0);

        auto f = [&](int t) -> bool {
            int i = 0, j = 0, res = 0;
            while (i < n) {
                res = 0;
                while (i < n && res <= t) res += nums[i++];
                if (res > t) i--;
                j++;
            }
            return j <= k && res <= t;
        };

        int ans = -1;
        while (l <= r) {
            int mid = (l + r) >> 1;
            if (f(mid)) ans = mid, r = mid - 1;
            else l = mid + 1;
        }
        assert(ans != -1);
        return ans;
    }
};