class Solution {
public:
    long long continuousSubarrays(vector<int>& nums) {
        vector<int> cnt(3), a(3);
        int l = 0, n = nums.size();

        auto f = [&](int val) -> int {
            for (int i = 0; i < 3; ++i)
                if (a[i] == val) return i;
            return -1;
        };

        long long ans = 0;

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (cnt[j] > 0 && abs(nums[i] - a[j]) > 2) {
                    while (cnt[j] > 0) {
                        --cnt[f(nums[l++])];
                    }
                }
            }
            int ind = f(nums[i]);
            if (ind == -1) {
                for (int j = 0; j < 3; ++j) {
                    if (cnt[j] == 0) {
                        a[j] = nums[i];
                        ++cnt[j];
                        break;
                    }
                }
            }
            else ++cnt[ind];
            ans += (i - l + 1);
        }

        return ans;

    }
};

