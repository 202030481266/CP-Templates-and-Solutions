class Solution {
public:
    int maxNumOfMarkedIndices(vector<int>& nums) {
        sort(nums.begin(), nums.end());

        int n = nums.size();
        int ans = 0;
        int l = 0, r = n / 2;

        auto f = [&](int v) {
            for (int i = 0, j = n - v; i < v && j < n; ++i, ++j)
                if (nums[j] < 2 * nums[i]) return false;
            return true;
        };


        while (l <= r) {
            int mid = (l + r) >> 1;
            if (f(mid)) ans = mid, l = mid + 1;
            else r = mid - 1;
        }
        return 2 * ans;
    }
};