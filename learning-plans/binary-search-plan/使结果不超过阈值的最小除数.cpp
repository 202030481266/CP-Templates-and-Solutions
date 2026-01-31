class Solution {
public:
    int smallestDivisor(vector<int>& nums, int threshold) {
        int l = 0, r = *max_element(nums.begin(), nums.end());
        auto check = [&](int val) -> bool {
            long long sum = 0;
            for (int& v : nums)
                sum += (v % val == 0 ? v / val : v / val + 1);
            return sum <= 1ll * threshold;
        };
        while (l + 1 < r) {
            int mid = (l + r) >> 1;
            if (check(mid))
                r = mid;
            else
                l = mid;
        }
        return r;
    }
};